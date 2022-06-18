/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @constructor
 * @extends {WebInspector.SDKModel}
 * @param {!WebInspector.Target} target
 */
WebInspector.CSSStyleModel = function(target)
{
    WebInspector.SDKModel.call(this, WebInspector.CSSStyleModel, target);
    this._domModel = WebInspector.DOMModel.fromTarget(target);
    this._agent = target.cssAgent();
    WebInspector.targetManager.addEventListener(WebInspector.TargetManager.Events.SuspendStateChanged, this._suspendStateChanged, this);
    this._styleLoader = new WebInspector.CSSStyleModel.ComputedStyleLoader(this);
    target.resourceTreeModel.addEventListener(WebInspector.ResourceTreeModel.EventTypes.MainFrameNavigated, this._mainFrameNavigated, this);
    target.registerCSSDispatcher(new WebInspector.CSSDispatcher(this));
    this._agent.enable().then(this._wasEnabled.bind(this));
    /** @type {!Map.<string, !WebInspector.CSSStyleSheetHeader>} */
    this._styleSheetIdToHeader = new Map();
    /** @type {!Map.<string, !Object.<!PageAgent.FrameId, !Array.<!CSSAgent.StyleSheetId>>>} */
    this._styleSheetIdsForURL = new Map();
}

WebInspector.CSSStyleModel.PseudoStatePropertyName = "pseudoState";

/**
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!Array.<!CSSAgent.RuleMatch>|undefined} matchArray
 * @return {!Array.<!WebInspector.CSSRule>}
 */
WebInspector.CSSStyleModel.parseRuleMatchArrayPayload = function(cssModel, matchArray)
{
    if (!matchArray)
        return [];

    var result = [];
    for (var i = 0; i < matchArray.length; ++i)
        result.push(WebInspector.CSSRule.parsePayload(cssModel, matchArray[i].rule, matchArray[i].matchingSelectors));
    return result;
}

WebInspector.CSSStyleModel.Events = {
    MediaQueryResultChanged: "MediaQueryResultChanged",
    ModelWasEnabled: "ModelWasEnabled",
    PseudoStateForced: "PseudoStateForced",
    StyleSheetAdded: "StyleSheetAdded",
    StyleSheetChanged: "StyleSheetChanged",
    StyleSheetRemoved: "StyleSheetRemoved"
}

WebInspector.CSSStyleModel.MediaTypes = ["all", "braille", "embossed", "handheld", "print", "projection", "screen", "speech", "tty", "tv"];

WebInspector.CSSStyleModel.prototype = {
    /**
     * @return {!Promise.<!Array.<!WebInspector.CSSMedia>>}
     */
    mediaQueriesPromise: function()
    {
        /**
         * @param {?Protocol.Error} error
         * @param {?Array.<!CSSAgent.CSSMedia>} payload
         * @return {!Array.<!WebInspector.CSSMedia>}
         * @this {!WebInspector.CSSStyleModel}
         */
        function parsePayload(error, payload)
        {
            return !error && payload ? WebInspector.CSSMedia.parseMediaArrayPayload(this, payload) : [];
        }

        return this._agent.getMediaQueries(parsePayload.bind(this));
    },

    /**
     * @return {boolean}
     */
    isEnabled: function()
    {
        return this._isEnabled;
    },

    /**
     * @param {?Protocol.Error} error
     */
    _wasEnabled: function(error)
    {
        if (error) {
            console.error("Failed to enabled CSS agent: " + error);
            return;
        }
        this._isEnabled = true;
        this.dispatchEventToListeners(WebInspector.CSSStyleModel.Events.ModelWasEnabled);
    },

    /**
     * @param {!DOMAgent.NodeId} nodeId
     * @param {boolean} excludePseudo
     * @param {boolean} excludeInherited
     * @return {!Promise.<?WebInspector.CSSStyleModel.MatchedStyleResult>}
     */
    matchedStylesPromise: function(nodeId, excludePseudo, excludeInherited)
    {
        /**
         * @param {?Protocol.Error} error
         * @param {!Array.<!CSSAgent.RuleMatch>=} matchedPayload
         * @param {!Array.<!CSSAgent.PseudoIdMatches>=} pseudoPayload
         * @param {!Array.<!CSSAgent.InheritedStyleEntry>=} inheritedPayload
         * @return {?WebInspector.CSSStyleModel.MatchedStyleResult}
         * @this {WebInspector.CSSStyleModel}
         */
        function callback(error, matchedPayload, pseudoPayload, inheritedPayload)
        {
            if (error)
                return null;
            
            var matchedRules = WebInspector.CSSStyleModel.parseRuleMatchArrayPayload(this, matchedPayload);

            var pseudoElements = [];
            if (pseudoPayload) {
                for (var i = 0; i < pseudoPayload.length; ++i) {
                    var entryPayload = pseudoPayload[i];
                    pseudoElements.push(new WebInspector.CSSStyleModel.PseudoElementMatches(entryPayload.pseudoId, WebInspector.CSSStyleModel.parseRuleMatchArrayPayload(this, entryPayload.matches)));
                }
            }

            var inherited = [];
            if (inheritedPayload) {
                for (var i = 0; i < inheritedPayload.length; ++i) {
                    var entryPayload = inheritedPayload[i];
                    var inlineStyle = entryPayload.inlineStyle ? WebInspector.CSSStyleDeclaration.parsePayload(this, entryPayload.inlineStyle) : null;
                    var matchedCSSRules = entryPayload.matchedCSSRules ? WebInspector.CSSStyleModel.parseRuleMatchArrayPayload(this, entryPayload.matchedCSSRules) : null;
                    inherited.push(new WebInspector.CSSStyleModel.InheritedMatches(inlineStyle, matchedCSSRules));

                }
            }
            return new WebInspector.CSSStyleModel.MatchedStyleResult(matchedRules, inherited, pseudoElements);
        }

        return this._agent.getMatchedStylesForNode(nodeId, excludePseudo, excludeInherited, callback.bind(this));
    },

    /**
     * @param {!DOMAgent.NodeId} nodeId
     * @return {!Promise.<?WebInspector.CSSStyleDeclaration>}
     */
    computedStylePromise: function(nodeId)
    {
        return this._styleLoader.computedStylePromise(nodeId);
    },

    /**
     * @param {number} nodeId
     * @return {!Promise.<?Array.<!CSSAgent.PlatformFontUsage>>}
     */
    platformFontsPromise: function(nodeId)
    {
        /**
         * @param {?Protocol.Error} error
         * @param {?Array.<!CSSAgent.PlatformFontUsage>} fonts
         * @return {?Array.<!CSSAgent.PlatformFontUsage>}
         */
        function platformFontsCallback(error, fonts)
        {
            return !error && fonts ? fonts : null;
        }

        return this._agent.getPlatformFontsForNode(nodeId, platformFontsCallback);
    },

    /**
     * @return {!Array.<!WebInspector.CSSStyleSheetHeader>}
     */
    allStyleSheets: function()
    {
        var values = this._styleSheetIdToHeader.valuesArray();
        /**
         * @param {!WebInspector.CSSStyleSheetHeader} a
         * @param {!WebInspector.CSSStyleSheetHeader} b
         * @return {number}
         */
        function styleSheetComparator(a, b)
        {
            if (a.sourceURL < b.sourceURL)
                return -1;
            else if (a.sourceURL > b.sourceURL)
                return 1;
            return a.startLine - b.startLine || a.startColumn - b.startColumn;
        }
        values.sort(styleSheetComparator);

        return values;
    },

    /**
     * @param {!DOMAgent.NodeId} nodeId
     * @return {!Promise.<?WebInspector.CSSStyleModel.InlineStyleResult>}
     */
    inlineStylesPromise: function(nodeId)
    {
        /**
         * @param {?Protocol.Error} error
         * @param {?CSSAgent.CSSStyle=} inlinePayload
         * @param {?CSSAgent.CSSStyle=} attributesStylePayload
         * @return {?WebInspector.CSSStyleModel.InlineStyleResult}
         * @this {WebInspector.CSSStyleModel}
         */
        function callback(error, inlinePayload, attributesStylePayload)
        {
            if (error || !inlinePayload)
                return null;
            var inlineStyle = inlinePayload ? WebInspector.CSSStyleDeclaration.parsePayload(this, inlinePayload) : null;
            var attributesStyle = attributesStylePayload ? WebInspector.CSSStyleDeclaration.parsePayload(this, attributesStylePayload) : null;
            return new WebInspector.CSSStyleModel.InlineStyleResult(inlineStyle, attributesStyle);
        }

        return this._agent.getInlineStylesForNode(nodeId, callback.bind(this));
    },

    /**
     * @param {!WebInspector.DOMNode} node
     * @param {string} pseudoClass
     * @param {boolean} enable
     * @return {boolean}
     */
    forcePseudoState: function(node, pseudoClass, enable)
    {
        var pseudoClasses = node.getUserProperty(WebInspector.CSSStyleModel.PseudoStatePropertyName) || [];
        if (enable) {
            if (pseudoClasses.indexOf(pseudoClass) >= 0)
                return false;
            pseudoClasses.push(pseudoClass);
            node.setUserProperty(WebInspector.CSSStyleModel.PseudoStatePropertyName, pseudoClasses);
        } else {
            if (pseudoClasses.indexOf(pseudoClass) < 0)
                return false;
            pseudoClasses.remove(pseudoClass);
            if (!pseudoClasses.length)
                node.removeUserProperty(WebInspector.CSSStyleModel.PseudoStatePropertyName);
        }

        this._agent.forcePseudoState(node.id, pseudoClasses);
        this.dispatchEventToListeners(WebInspector.CSSStyleModel.Events.PseudoStateForced, { node: node, pseudoClass: pseudoClass, enable: enable });
        return true;
    },

    /**
     * @param {!CSSAgent.CSSRule} rule
     * @param {!DOMAgent.NodeId} nodeId
     * @param {string} newSelector
     * @param {function(?WebInspector.CSSRule)} userCallback
     */
    setRuleSelector: function(rule, nodeId, newSelector, userCallback)
    {
        /**
         * @param {?Protocol.Error} error
         * @param {?CSSAgent.CSSRule} rulePayload
         * @return {?CSSAgent.CSSRule}
         * @this {WebInspector.CSSStyleModel}
         */
        function callback(error, rulePayload)
        {
            if (error || !rulePayload)
                return null;
            this._domModel.markUndoableState();
            return rulePayload;
        }

        if (!rule.styleSheetId)
            throw "No rule stylesheet id";
        WebInspector.userMetrics.StyleRuleEdited.record();
        this._agent.setRuleSelector(rule.styleSheetId, rule.selectorRange, newSelector, callback.bind(this))
            .then(this._computeMatchingSelectors.bind(this, nodeId))
            .catchException(null)
            .then(userCallback);
    },

    /**
     * @param {!WebInspector.CSSMedia} media
     * @param {string} newMediaText
     * @param {function(?WebInspector.CSSMedia)} userCallback
     */
    setMediaText: function(media, newMediaText, userCallback)
    {
        /**
         * @param {?Protocol.Error} error
         * @param {!CSSAgent.CSSMedia} mediaPayload
         * @return {?WebInspector.CSSMedia}
         * @this {WebInspector.CSSStyleModel}
         */
        function parsePayload(error, mediaPayload)
        {
            if (!mediaPayload)
                return null;
            this._domModel.markUndoableState();
            return WebInspector.CSSMedia.parsePayload(this, mediaPayload);
        }

        console.assert(!!media.parentStyleSheetId);
        WebInspector.userMetrics.StyleRuleEdited.record();
        this._agent.setMediaText(media.parentStyleSheetId, media.range, newMediaText, parsePayload.bind(this))
            .catchException(null)
            .then(userCallback);
    },

    /**
     * @param {!DOMAgent.NodeId} nodeId
     * @param {?CSSAgent.CSSRule} rulePayload
     * @return {!Promise.<?WebInspector.CSSRule>}
     */
    _computeMatchingSelectors: function(nodeId, rulePayload)
    {
        var ownerDocumentId = this._ownerDocumentId(nodeId);
        if (!ownerDocumentId || !rulePayload)
            return Promise.resolve(/** @type {?WebInspector.CSSRule} */(null));
        var rule = WebInspector.CSSRule.parsePayload(this, rulePayload);
        var matchingSelectors = [];
        var allSelectorsBarrier = new CallbackBarrier();
        for (var i = 0; i < rule.selectors.length; ++i) {
            var selector = rule.selectors[i];
            var boundCallback = allSelectorsBarrier.createCallback(selectorQueried.bind(null, i, nodeId, matchingSelectors));
            this._domModel.querySelectorAll(ownerDocumentId, selector.value, boundCallback);
        }
        return new Promise(promiseConstructor);

        /**
         * @param {function(!WebInspector.CSSRule)} resolve
         */
        function promiseConstructor(resolve)
        {
            allSelectorsBarrier.callWhenDone(function() {
                rule.matchingSelectors = matchingSelectors;
                resolve(rule);
            });
        }

        /**
         * @param {number} index
         * @param {!DOMAgent.NodeId} nodeId
         * @param {!Array.<number>} matchingSelectors
         * @param {!Array.<!DOMAgent.NodeId>=} matchingNodeIds
         */
        function selectorQueried(index, nodeId, matchingSelectors, matchingNodeIds)
        {
            if (!matchingNodeIds)
                return;
            if (matchingNodeIds.indexOf(nodeId) !== -1)
                matchingSelectors.push(index);
        }
    },

    /**
     * @param {!CSSAgent.StyleSheetId} styleSheetId
     * @param {!WebInspector.DOMNode} node
     * @param {string} ruleText
     * @param {!WebInspector.TextRange} ruleLocation
     * @param {function(?WebInspector.CSSRule)} userCallback
     */
    addRule: function(styleSheetId, node, ruleText, ruleLocation, userCallback)
    {
        this._agent.addRule(styleSheetId, ruleText, ruleLocation, parsePayload.bind(this))
            .then(this._computeMatchingSelectors.bind(this, node.id))
            .catchException(null)
            .then(userCallback);

        /**
         * @param {?Protocol.Error} error
         * @param {?CSSAgent.CSSRule} rulePayload
         * @return {?CSSAgent.CSSRule}
         * @this {WebInspector.CSSStyleModel}
         */
        function parsePayload(error, rulePayload)
        {
            if (error || !rulePayload)
                return null;
            this._domModel.markUndoableState();
            return rulePayload;
        }
    },

    /**
     * @param {!WebInspector.DOMNode} node
     * @param {function(?WebInspector.CSSStyleSheetHeader)} userCallback
     */
    requestViaInspectorStylesheet: function(node, userCallback)
    {
        var frameId = node.frameId() || this.target().resourceTreeModel.mainFrame.id;
        var headers = this._styleSheetIdToHeader.valuesArray();
        for (var i = 0; i < headers.length; ++i) {
            var styleSheetHeader = headers[i];
            if (styleSheetHeader.frameId === frameId && styleSheetHeader.isViaInspector()) {
                userCallback(styleSheetHeader);
                return;
            }
        }

        /**
         * @param {?Protocol.Error} error
         * @param {?CSSAgent.StyleSheetId} styleSheetId
         * @return {?WebInspector.CSSStyleSheetHeader}
         * @this {WebInspector.CSSStyleModel}
         */
        function innerCallback(error, styleSheetId)
        {
            return !error && styleSheetId ? this._styleSheetIdToHeader.get(styleSheetId) || null : null;
        }

        this._agent.createStyleSheet(frameId, innerCallback.bind(this))
            .catchException(null)
            .then(userCallback)
    },

    mediaQueryResultChanged: function()
    {
        this.dispatchEventToListeners(WebInspector.CSSStyleModel.Events.MediaQueryResultChanged);
    },

    /**
     * @param {!CSSAgent.StyleSheetId} id
     * @return {?WebInspector.CSSStyleSheetHeader}
     */
    styleSheetHeaderForId: function(id)
    {
        return this._styleSheetIdToHeader.get(id) || null;
    },

    /**
     * @return {!Array.<!WebInspector.CSSStyleSheetHeader>}
     */
    styleSheetHeaders: function()
    {
        return this._styleSheetIdToHeader.valuesArray();
    },

    /**
     * @param {!DOMAgent.NodeId} nodeId
     * @return {?DOMAgent.NodeId}
     */
    _ownerDocumentId: function(nodeId)
    {
        var node = this._domModel.nodeForId(nodeId);
        if (!node)
            return null;
        return node.ownerDocument ? node.ownerDocument.id : null;
    },

    /**
     * @param {!CSSAgent.StyleSheetId} styleSheetId
     */
    _fireStyleSheetChanged: function(styleSheetId)
    {
        if (!styleSheetId || !this.hasEventListeners(WebInspector.CSSStyleModel.Events.StyleSheetChanged))
            return;

        this.dispatchEventToListeners(WebInspector.CSSStyleModel.Events.StyleSheetChanged, { styleSheetId: styleSheetId });
    },

    /**
     * @param {!CSSAgent.CSSStyleSheetHeader} header
     */
    _styleSheetAdded: function(header)
    {
        console.assert(!this._styleSheetIdToHeader.get(header.styleSheetId));
        var styleSheetHeader = new WebInspector.CSSStyleSheetHeader(this, header);
        this._styleSheetIdToHeader.set(header.styleSheetId, styleSheetHeader);
        var url = styleSheetHeader.resourceURL();
        if (!this._styleSheetIdsForURL.get(url))
            this._styleSheetIdsForURL.set(url, {});
        var frameIdToStyleSheetIds = this._styleSheetIdsForURL.get(url);
        var styleSheetIds = frameIdToStyleSheetIds[styleSheetHeader.frameId];
        if (!styleSheetIds) {
            styleSheetIds = [];
            frameIdToStyleSheetIds[styleSheetHeader.frameId] = styleSheetIds;
        }
        styleSheetIds.push(styleSheetHeader.id);
        this.dispatchEventToListeners(WebInspector.CSSStyleModel.Events.StyleSheetAdded, styleSheetHeader);
    },

    /**
     * @param {!CSSAgent.StyleSheetId} id
     */
    _styleSheetRemoved: function(id)
    {
        var header = this._styleSheetIdToHeader.get(id);
        console.assert(header);
        if (!header)
            return;
        this._styleSheetIdToHeader.remove(id);
        var url = header.resourceURL();
        var frameIdToStyleSheetIds = /** @type {!Object.<!PageAgent.FrameId, !Array.<!CSSAgent.StyleSheetId>>} */ (this._styleSheetIdsForURL.get(url));
        console.assert(frameIdToStyleSheetIds, "No frameId to styleSheetId map is available for given style sheet URL.");
        frameIdToStyleSheetIds[header.frameId].remove(id);
        if (!frameIdToStyleSheetIds[header.frameId].length) {
            delete frameIdToStyleSheetIds[header.frameId];
            if (!Object.keys(frameIdToStyleSheetIds).length)
                this._styleSheetIdsForURL.remove(url);
        }
        this.dispatchEventToListeners(WebInspector.CSSStyleModel.Events.StyleSheetRemoved, header);
    },

    /**
     * @param {string} url
     * @return {!Array.<!CSSAgent.StyleSheetId>}
     */
    styleSheetIdsForURL: function(url)
    {
        var frameIdToStyleSheetIds = this._styleSheetIdsForURL.get(url);
        if (!frameIdToStyleSheetIds)
            return [];

        var result = [];
        for (var frameId in frameIdToStyleSheetIds)
            result = result.concat(frameIdToStyleSheetIds[frameId]);
        return result;
    },

    /**
     * @param {!CSSAgent.StyleSheetId} styleSheetId
     * @param {string} newText
     * @param {boolean} majorChange
     * @return {!Promise.<?Protocol.Error>}
     */
    setStyleSheetText: function(styleSheetId, newText, majorChange)
    {
        var header = this._styleSheetIdToHeader.get(styleSheetId);
        console.assert(header);
        return header._setContentPromise(newText).then(callback.bind(this));

        /**
         * @param {?Protocol.Error} error
         * @return {?Protocol.Error}
         * @this {WebInspector.CSSStyleModel}
         */
        function callback(error)
        {
            if (!error && majorChange)
                this._domModel.markUndoableState();

            return error;
        }
    },

    _mainFrameNavigated: function()
    {
        this._resetStyleSheets();
    },

    _resetStyleSheets: function()
    {
        var headers = this._styleSheetIdToHeader.valuesArray();
        this._styleSheetIdsForURL.clear();
        this._styleSheetIdToHeader.clear();
        for (var i = 0; i < headers.length; ++i)
            this.dispatchEventToListeners(WebInspector.CSSStyleModel.Events.StyleSheetRemoved, headers[i]);
    },

    _suspendStateChanged: function()
    {
        if (WebInspector.targetManager.allTargetsSuspended()) {
            this._agent.disable();
            this._isEnabled = false;
        } else {
            this._resetStyleSheets();
            this._agent.enable().then(this._wasEnabled.bind(this));
        }
    },

    __proto__: WebInspector.SDKModel.prototype
}

/**
 * @constructor
 * @extends {WebInspector.SDKObject}
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!CSSAgent.StyleSheetId} styleSheetId
 * @param {string} url
 * @param {number} lineNumber
 * @param {number=} columnNumber
 */
WebInspector.CSSLocation = function(cssModel, styleSheetId, url, lineNumber, columnNumber)
{
    WebInspector.SDKObject.call(this, cssModel.target());
    this._cssModel = cssModel;
    this.styleSheetId = styleSheetId;
    this.url = url;
    this.lineNumber = lineNumber;
    this.columnNumber = columnNumber || 0;
}

WebInspector.CSSLocation.prototype = {
    /**
     * @return {!WebInspector.CSSStyleModel}
     */
    cssModel: function()
    {
        return this._cssModel;
    },

    __proto__: WebInspector.SDKObject.prototype
}

/**
 * @constructor
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!CSSAgent.CSSStyle} payload
 */
WebInspector.CSSStyleDeclaration = function(cssModel, payload)
{
    this._cssModel = cssModel;
    this.styleSheetId = payload.styleSheetId;
    this.range = payload.range ? WebInspector.TextRange.fromObject(payload.range) : null;

    var shorthandEntries = payload.shorthandEntries;
    /** @type {!Map.<string, string>} */
    this._shorthandValues = new Map();
    /** @type {!Set.<string>} */
    this._shorthandIsImportant = new Set();
    for (var i = 0; i < shorthandEntries.length; ++i) {
        this._shorthandValues.set(shorthandEntries[i].name, shorthandEntries[i].value);
        if (shorthandEntries[i].important)
            this._shorthandIsImportant.add(shorthandEntries[i].name);
    }

    this._livePropertyMap = {}; // LIVE properties (source-based or style-based) : { name -> CSSProperty }
    this._allProperties = []; // ALL properties: [ CSSProperty ]
    this.__disabledProperties = {}; // DISABLED properties: { index -> CSSProperty }
    var payloadPropertyCount = payload.cssProperties.length;

    for (var i = 0; i < payloadPropertyCount; ++i) {
        var property = WebInspector.CSSProperty.parsePayload(this, i, payload.cssProperties[i]);
        this._allProperties.push(property);
    }

    this._computeActiveProperties();

    var propertyIndex = 0;
    for (var i = 0; i < this._allProperties.length; ++i) {
        var property = this._allProperties[i];
        if (property.disabled)
            this.__disabledProperties[i] = property;
        if (!property.active && !property.styleBased)
            continue;
        var name = property.name;
        this[propertyIndex] = name;
        this._livePropertyMap[name] = property;
        ++propertyIndex;
    }
    this.length = propertyIndex;
    if ("cssText" in payload)
        this.cssText = payload.cssText;
}

/**
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @return {!WebInspector.CSSStyleDeclaration}
 */
WebInspector.CSSStyleDeclaration.createDummyStyle = function(cssModel)
{
    var dummyPayload = {
        shorthandEntries: [],
        cssProperties: []
    };
    return new WebInspector.CSSStyleDeclaration(cssModel, dummyPayload);
}

/**
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!CSSAgent.CSSStyle} payload
 * @return {!WebInspector.CSSStyleDeclaration}
 */
WebInspector.CSSStyleDeclaration.parsePayload = function(cssModel, payload)
{
    return new WebInspector.CSSStyleDeclaration(cssModel, payload);
}

/**
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!Array.<!CSSAgent.CSSComputedStyleProperty>} payload
 * @return {!WebInspector.CSSStyleDeclaration}
 */
WebInspector.CSSStyleDeclaration.parseComputedStylePayload = function(cssModel, payload)
{
    var newPayload = /** @type {!CSSAgent.CSSStyle} */ ({ cssProperties: [], shorthandEntries: [], width: "", height: "" });
    if (payload)
        newPayload.cssProperties = /** @type {!Array.<!CSSAgent.CSSProperty>} */ (payload);

    return new WebInspector.CSSStyleDeclaration(cssModel, newPayload);
}

WebInspector.CSSStyleDeclaration.prototype = {
    /**
     * @return {!WebInspector.Target}
     */
    target: function()
    {
        return this._cssModel.target();
    },

    /**
     * @return {!WebInspector.CSSStyleModel}
     */
    cssModel: function()
    {
        return this._cssModel;
    },

    /**
     * @param {string} styleSheetId
     * @param {!WebInspector.TextRange} oldRange
     * @param {!WebInspector.TextRange} newRange
     */
    sourceStyleSheetEdited: function(styleSheetId, oldRange, newRange)
    {
        if (this.styleSheetId !== styleSheetId)
            return;
        if (this.range)
            this.range = this.range.rebaseAfterTextEdit(oldRange, newRange);
        for (var i = 0; i < this._allProperties.length; ++i)
            this._allProperties[i].sourceStyleSheetEdited(styleSheetId, oldRange, newRange);
    },

    _computeActiveProperties: function()
    {
        var activeProperties = {};
        for (var i = this._allProperties.length - 1; i >= 0; --i) {
            var property = this._allProperties[i];
            if (property.styleBased || property.disabled)
                continue;
            property._setActive(false);
            if (!property.parsedOk)
                continue;
            var canonicalName = WebInspector.CSSMetadata.canonicalPropertyName(property.name);
            var activeProperty = activeProperties[canonicalName];
            if (!activeProperty || (!activeProperty.important && property.important))
                activeProperties[canonicalName] = property;
        }
        for (var propertyName in activeProperties) {
            var property = activeProperties[propertyName];
            property._setActive(true);
        }
    },

    get allProperties()
    {
        return this._allProperties;
    },

    /**
     * @param {string} name
     * @return {?WebInspector.CSSProperty}
     */
    getLiveProperty: function(name)
    {
        return this._livePropertyMap[name] || null;
    },

    /**
     * @param {string} name
     * @return {string}
     */
    getPropertyValue: function(name)
    {
        var property = this._livePropertyMap[name];
        return property ? property.value : "";
    },

    /**
     * @param {string} name
     * @return {boolean}
     */
    isPropertyImplicit: function(name)
    {
        var property = this._livePropertyMap[name];
        return property ? property.implicit : "";
    },

    /**
     * @param {string} name
     * @return {!Array.<!WebInspector.CSSProperty>}
     */
    longhandProperties: function(name)
    {
        var longhands = WebInspector.CSSMetadata.cssPropertiesMetainfo.longhands(name);
        var result = [];
        for (var i = 0; longhands && i < longhands.length; ++i) {
            var property = this._livePropertyMap[longhands[i]];
            if (property)
                result.push(property);
        }
        return result;
    },

    /**
     * @param {string} shorthandProperty
     * @return {string}
     */
    shorthandValue: function(shorthandProperty)
    {
        return this._shorthandValues.get(shorthandProperty) || "";
    },

    /**
     * @param {string} shorthandProperty
     * @return {boolean}
     */
    shorthandIsImportant: function(shorthandProperty)
    {
        return this._shorthandIsImportant.has(shorthandProperty);
    },

    /**
     * @param {number} index
     * @return {?WebInspector.CSSProperty}
     */
    propertyAt: function(index)
    {
        return (index < this.allProperties.length) ? this.allProperties[index] : null;
    },

    /**
     * @return {number}
     */
    pastLastSourcePropertyIndex: function()
    {
        for (var i = this.allProperties.length - 1; i >= 0; --i) {
            if (this.allProperties[i].range)
                return i + 1;
        }
        return 0;
    },

    /**
     * @param {number} index
     * @return {!WebInspector.TextRange}
     */
    _insertionRange: function(index)
    {
        var property = this.propertyAt(index);
        return property && property.range ? property.range.collapseToStart() : this.range.collapseToEnd();
    },

    /**
     * @param {number=} index
     * @return {!WebInspector.CSSProperty}
     */
    newBlankProperty: function(index)
    {
        index = (typeof index === "undefined") ? this.pastLastSourcePropertyIndex() : index;
        var property = new WebInspector.CSSProperty(this, index, "", "", false, false, true, false, "", this._insertionRange(index));
        property._setActive(true);
        return property;
    },

    /**
     * @param {string} text
     * @param {boolean} majorChange
     * @param {function(?WebInspector.CSSStyleDeclaration)} userCallback
     */
    setText: function(text, majorChange, userCallback)
    {
        if (!this.styleSheetId) {
            userCallback(null);
            return;
        }

        /**
         * @param {?Protocol.Error} error
         * @param {?CSSAgent.CSSStyle} stylePayload
         * @return {?WebInspector.CSSStyleDeclaration}
         * @this {WebInspector.CSSStyleDeclaration}
         */
        function parsePayload(error, stylePayload)
        {
            if (error || !stylePayload)
                return null;

            if (majorChange)
                this._cssModel._domModel.markUndoableState();
            return WebInspector.CSSStyleDeclaration.parsePayload(this._cssModel, stylePayload);
        }

        this._cssModel._agent.setStyleText(this.styleSheetId, this.range.serializeToObject(), text, parsePayload.bind(this))
            .catchException(null)
            .then(userCallback)
    },

    /**
     * @param {number} index
     * @param {string} name
     * @param {string} value
     * @param {function(?WebInspector.CSSStyleDeclaration)=} userCallback
     */
    insertPropertyAt: function(index, name, value, userCallback)
    {
        this.newBlankProperty(index).setText(name + ": " + value + ";", false, true, userCallback);
    },

    /**
     * @param {string} name
     * @param {string} value
     * @param {function(?WebInspector.CSSStyleDeclaration)=} userCallback
     */
    appendProperty: function(name, value, userCallback)
    {
        this.insertPropertyAt(this.allProperties.length, name, value, userCallback);
    }
}

/**
 * @constructor
 * @param {!CSSAgent.Selector} payload
 */
WebInspector.CSSRuleSelector = function(payload)
{
    this.value = payload.value;
    if (payload.range)
        this.range = WebInspector.TextRange.fromObject(payload.range);
}

/**
 * @param {!CSSAgent.Selector} payload
 * @return {!WebInspector.CSSRuleSelector}
 */
WebInspector.CSSRuleSelector.parsePayload = function(payload)
{
    return new WebInspector.CSSRuleSelector(payload);
}

WebInspector.CSSRuleSelector.prototype = {
    /**
     * @param {!WebInspector.TextRange} oldRange
     * @param {!WebInspector.TextRange} newRange
     */
    sourceStyleRuleEdited: function(oldRange, newRange)
    {
        if (!this.range)
            return;
        this.range = this.range.rebaseAfterTextEdit(oldRange, newRange);
    }
}

/**
 * @constructor
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!CSSAgent.CSSRule} payload
 * @param {!Array.<number>=} matchingSelectors
 */
WebInspector.CSSRule = function(cssModel, payload, matchingSelectors)
{
    this._cssModel = cssModel;
    this.styleSheetId = payload.styleSheetId;
    if (matchingSelectors)
        this.matchingSelectors = matchingSelectors;

    /** @type {!Array.<!WebInspector.CSSRuleSelector>} */
    this.selectors = [];
    for (var i = 0; i < payload.selectorList.selectors.length; ++i) {
        var selectorPayload = payload.selectorList.selectors[i];
        this.selectors.push(WebInspector.CSSRuleSelector.parsePayload(selectorPayload));
    }
    this.selectorText = this.selectors.select("value").join(", ");

    var firstRange = this.selectors[0].range;
    if (firstRange) {
        var lastRange = this.selectors.peekLast().range;
        this.selectorRange = new WebInspector.TextRange(firstRange.startLine, firstRange.startColumn, lastRange.endLine, lastRange.endColumn);
    }
    if (this.styleSheetId) {
        var styleSheetHeader = cssModel.styleSheetHeaderForId(this.styleSheetId);
        this.sourceURL = styleSheetHeader.sourceURL;
    }
    this.origin = payload.origin;
    this.style = WebInspector.CSSStyleDeclaration.parsePayload(this._cssModel, payload.style);
    this.style.parentRule = this;
    if (payload.media)
        this.media = WebInspector.CSSMedia.parseMediaArrayPayload(cssModel, payload.media);
    this._setFrameId();
}

/**
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!CSSAgent.CSSRule} payload
 * @param {!Array.<number>=} matchingIndices
 * @return {!WebInspector.CSSRule}
 */
WebInspector.CSSRule.parsePayload = function(cssModel, payload, matchingIndices)
{
    return new WebInspector.CSSRule(cssModel, payload, matchingIndices);
}

WebInspector.CSSRule.prototype = {
    /**
     * @param {string} styleSheetId
     * @param {!WebInspector.TextRange} oldRange
     * @param {!WebInspector.TextRange} newRange
     */
    sourceStyleSheetEdited: function(styleSheetId, oldRange, newRange)
    {
        this._sourceStyleSheetEditedWithMedia(styleSheetId, oldRange, newRange, null, null);
    },

    /**
     * @param {string} styleSheetId
     * @param {!WebInspector.TextRange} oldRange
     * @param {!WebInspector.TextRange} newRange
     * @param {?WebInspector.CSSMedia} oldMedia
     * @param {?WebInspector.CSSMedia} newMedia
     */
    _sourceStyleSheetEditedWithMedia: function(styleSheetId, oldRange, newRange, oldMedia, newMedia)
    {
        if (this.styleSheetId === styleSheetId) {
            if (this.selectorRange)
                this.selectorRange = this.selectorRange.rebaseAfterTextEdit(oldRange, newRange);
            for (var i = 0; i < this.selectors.length; ++i)
                this.selectors[i].sourceStyleRuleEdited(oldRange, newRange);
        }
        if (this.media) {
            for (var i = 0; i < this.media.length; ++i) {
                if (oldMedia && newMedia && oldMedia.equal(this.media[i])) {
                    this.media[i] = newMedia;
                } else {
                    this.media[i].sourceStyleSheetEdited(styleSheetId, oldRange, newRange);
                }
            }
        }
        this.style.sourceStyleSheetEdited(styleSheetId, oldRange, newRange);
    },

    /**
     * @param {!WebInspector.CSSMedia} oldMedia
     * @param {!WebInspector.CSSMedia} newMedia
     */
    mediaEdited: function(oldMedia, newMedia)
    {
        this._sourceStyleSheetEditedWithMedia(/** @type {string} */ (oldMedia.parentStyleSheetId), oldMedia.range, newMedia.range, oldMedia, newMedia);
    },

    _setFrameId: function()
    {
        if (!this.styleSheetId)
            return;
        var styleSheetHeader = this._cssModel.styleSheetHeaderForId(this.styleSheetId);
        this.frameId = styleSheetHeader.frameId;
    },

    /**
     * @return {string}
     */
    resourceURL: function()
    {
        if (!this.styleSheetId)
            return "";
        var styleSheetHeader = this._cssModel.styleSheetHeaderForId(this.styleSheetId);
        return styleSheetHeader.resourceURL();
    },

    /**
     * @param {number} selectorIndex
     * @return {number}
     */
    lineNumberInSource: function(selectorIndex)
    {
        var selector = this.selectors[selectorIndex];
        if (!selector || !selector.range || !this.styleSheetId)
            return 0;
        var styleSheetHeader = this._cssModel.styleSheetHeaderForId(this.styleSheetId);
        return styleSheetHeader.lineNumberInSource(selector.range.startLine);
    },

    /**
     * @param {number} selectorIndex
     * @return {number|undefined}
     */
    columnNumberInSource: function(selectorIndex)
    {
        var selector = this.selectors[selectorIndex];
        if (!selector || !selector.range || !this.styleSheetId)
            return undefined;
        var styleSheetHeader = this._cssModel.styleSheetHeaderForId(this.styleSheetId);
        console.assert(styleSheetHeader);
        return styleSheetHeader.columnNumberInSource(selector.range.startLine, selector.range.startColumn);
    },

    get isUserAgent()
    {
        return this.origin === "user-agent";
    },

    get isInjected()
    {
        return this.origin === "injected";
    },

    get isViaInspector()
    {
        return this.origin === "inspector";
    },

    get isRegular()
    {
        return this.origin === "regular";
    }
}

/**
 * @constructor
 * @param {?WebInspector.CSSStyleDeclaration} ownerStyle
 * @param {number} index
 * @param {string} name
 * @param {string} value
 * @param {boolean} important
 * @param {boolean} disabled
 * @param {boolean} parsedOk
 * @param {boolean} implicit
 * @param {?string=} text
 * @param {!CSSAgent.SourceRange=} range
 */
WebInspector.CSSProperty = function(ownerStyle, index, name, value, important, disabled, parsedOk, implicit, text, range)
{
    this.ownerStyle = ownerStyle;
    this.index = index;
    this.name = name;
    this.value = value;
    this.important = important;
    this.disabled = disabled;
    this.parsedOk = parsedOk;
    this.implicit = implicit;
    this.text = text;
    this.range = range ? WebInspector.TextRange.fromObject(range) : null;
}

/**
 * @param {?WebInspector.CSSStyleDeclaration} ownerStyle
 * @param {number} index
 * @param {!CSSAgent.CSSProperty} payload
 * @return {!WebInspector.CSSProperty}
 */
WebInspector.CSSProperty.parsePayload = function(ownerStyle, index, payload)
{
    // The following default field values are used in the payload:
    // important: false
    // parsedOk: true
    // implicit: false
    // disabled: false
    var result = new WebInspector.CSSProperty(
        ownerStyle, index, payload.name, payload.value, payload.important || false, payload.disabled || false, ("parsedOk" in payload) ? !!payload.parsedOk : true, !!payload.implicit, payload.text, payload.range);
    return result;
}

WebInspector.CSSProperty.prototype = {
    /**
     * @param {string} styleSheetId
     * @param {!WebInspector.TextRange} oldRange
     * @param {!WebInspector.TextRange} newRange
     */
    sourceStyleSheetEdited: function(styleSheetId, oldRange, newRange)
    {
        if (this.ownerStyle.styleSheetId !== styleSheetId)
            return;
        if (this.range)
            this.range = this.range.rebaseAfterTextEdit(oldRange, newRange);
    },

    /**
     * @param {boolean} active
     */
    _setActive: function(active)
    {
        this._active = active;
    },

    get propertyText()
    {
        if (this.text !== undefined)
            return this.text;

        if (this.name === "")
            return "";
        return this.name + ": " + this.value + (this.important ? " !important" : "") + ";";
    },

    get isLive()
    {
        return this.active || this.styleBased;
    },

    get active()
    {
        return typeof this._active === "boolean" && this._active;
    },

    get styleBased()
    {
        return !this.range;
    },

    get inactive()
    {
        return typeof this._active === "boolean" && !this._active;
    },

    /**
     * @param {string} propertyText
     * @param {boolean} majorChange
     * @param {boolean} overwrite
     * @param {function(?WebInspector.CSSStyleDeclaration)=} userCallback
     */
    setText: function(propertyText, majorChange, overwrite, userCallback)
    {
        if (!this.ownerStyle)
            throw "No ownerStyle for property";

        if (!this.ownerStyle.styleSheetId)
            throw "No owner style id";

        if (!this.range || !this.ownerStyle.range)
            throw "Style not editable";

        if (majorChange)
            WebInspector.userMetrics.StyleRuleEdited.record();

        if (overwrite && propertyText === this.propertyText) {
            if (majorChange)
                this.ownerStyle._cssModel._domModel.markUndoableState();
            if (userCallback)
                userCallback(this.ownerStyle);
            return;
        }

        var range = this.range.relativeTo(this.ownerStyle.range.startLine, this.ownerStyle.range.startColumn);
        var indentation = this.ownerStyle.cssText ? this._detectIndentation(this.ownerStyle.cssText) : WebInspector.moduleSetting("textEditorIndent").get();
        var endIntentation = this.ownerStyle.cssText ? indentation.substring(0, this.ownerStyle.range.endColumn) : "";
        var newStyleText = range.replaceInText(this.ownerStyle.cssText || "", ";" + propertyText);

        this._formatStyle(newStyleText, indentation, endIntentation, setStyleText.bind(this));

        /**
         * @param {string} styleText
         * @this {WebInspector.CSSProperty}
         */
        function setStyleText(styleText)
        {
            this.ownerStyle.setText(styleText, majorChange, callback);
        }

        /**
         * @param {?WebInspector.CSSStyleDeclaration} style
         */
        function callback(style)
        {
            if (userCallback)
                userCallback(style);
        }

        /**
         * @param {?WebInspector.CSSStyleDeclaration} style
         */
        function enabledCallback(style)
        {
            if (userCallback)
                userCallback(style);
        }
    },

    /**
     * @param {string} styleText
     * @param {string} indentation
     * @param {string} endIndentation
     * @param {function(string)} callback
     */
    _formatStyle: function(styleText, indentation, endIndentation, callback)
    {
        self.runtime.instancePromise(WebInspector.TokenizerFactory).then(processTokens);
        var result = "";

        /**
         * @param {!WebInspector.TokenizerFactory} tokenizerFactory
         */
        function processTokens(tokenizerFactory)
        {
            var tokenize = tokenizerFactory.createTokenizer("text/css");
            tokenize("*{" + styleText + "}", processToken);
            result = result.slice(0, result.length - 1);
            callback(result + (indentation ? "\n" + endIndentation : ""));
        }

        var lastWasSemicolon = true;
        var lastWasMeta = false;
        var insideProperty = false;
        /**
         * @param {string} token
         * @param {?string} tokenType
         * @param {number} column
         * @param {number} newColumn
         */
        function processToken(token, tokenType, column, newColumn)
        {
            if (newColumn <= 2)
                return;
            var isSemicolon = token === ";";
            if (isSemicolon && lastWasSemicolon)
                return;
            lastWasSemicolon = isSemicolon || (lastWasSemicolon && tokenType && tokenType.includes("css-comment")) || (lastWasSemicolon && !token.trim());

            // No formatting, only remove dupe ;
            if (!indentation) {
                result += token;
                return;
            }

            // Format line breaks.
            if (!insideProperty && !token.trim())
                return;
            if (tokenType && tokenType.includes("css-comment") && token.includes(":") && token.includes(";")) {
                result += "\n" + indentation + token;
                insideProperty = false;
                return;
            }

            if (isSemicolon)
                insideProperty = false;

            if (tokenType && (tokenType.includes("css-meta") || (tokenType.includes("css-property") && !lastWasMeta))) {
                result += "\n" + indentation;
                insideProperty = true;
            }
            result += token;

            lastWasMeta = tokenType && tokenType.includes("css-meta");
        }
    },

    /**
     * @param {string} text
     * @return {string}
     */
    _detectIndentation: function(text)
    {
        var lines = text.split("\n");
        if (lines.length < 2)
            return "";
        return WebInspector.TextUtils.lineIndent(lines[1]);
    },

    /**
     * @param {string} newValue
     * @param {boolean} majorChange
     * @param {boolean} overwrite
     * @param {function(?WebInspector.CSSStyleDeclaration)=} userCallback
     */
    setValue: function(newValue, majorChange, overwrite, userCallback)
    {
        var text = this.name + ": " + newValue + (this.important ? " !important" : "") + ";";
        this.setText(text, majorChange, overwrite, userCallback);
    },

    /**
     * @param {boolean} disabled
     * @param {function(?WebInspector.CSSStyleDeclaration)=} userCallback
     */
    setDisabled: function(disabled, userCallback)
    {
        if (!this.ownerStyle && userCallback)
            userCallback(null);
        if (disabled === this.disabled) {
            if (userCallback)
                userCallback(this.ownerStyle);
            return;
        }
        if (disabled)
            this.setText("/* " + this.text + " */", true, true, userCallback);
        else
            this.setText(this.text.substring(2, this.text.length - 2).trim(), true, true, userCallback);
    }
}

/**
 * @constructor
 * @param {!CSSAgent.MediaQuery} payload
 */
WebInspector.CSSMediaQuery = function(payload)
{
    this._active = payload.active;
    this._expressions = [];
    for (var j = 0; j < payload.expressions.length; ++j)
        this._expressions.push(WebInspector.CSSMediaQueryExpression.parsePayload(payload.expressions[j]));
}

/**
 * @param {!CSSAgent.MediaQuery} payload
 * @return {!WebInspector.CSSMediaQuery}
 */
WebInspector.CSSMediaQuery.parsePayload = function(payload)
{
    return new WebInspector.CSSMediaQuery(payload);
}

WebInspector.CSSMediaQuery.prototype = {
    /**
     * @return {boolean}
     */
    active: function()
    {
        return this._active;
    },

    /**
     * @return {!Array.<!WebInspector.CSSMediaQueryExpression>}
     */
    expressions: function()
    {
        return this._expressions;
    }
}

/**
 * @constructor
 * @param {!CSSAgent.MediaQueryExpression} payload
 */
WebInspector.CSSMediaQueryExpression = function(payload)
{
    this._value = payload.value;
    this._unit = payload.unit;
    this._feature = payload.feature;
    this._valueRange = payload.valueRange ? WebInspector.TextRange.fromObject(payload.valueRange) : null;
    this._computedLength = payload.computedLength || null;
}

/**
 * @param {!CSSAgent.MediaQueryExpression} payload
 * @return {!WebInspector.CSSMediaQueryExpression}
 */
WebInspector.CSSMediaQueryExpression.parsePayload = function(payload)
{
    return new WebInspector.CSSMediaQueryExpression(payload);
}

WebInspector.CSSMediaQueryExpression.prototype = {
    /**
     * @return {number}
     */
    value: function()
    {
        return this._value;
    },

    /**
     * @return {string}
     */
    unit: function()
    {
        return this._unit;
    },

    /**
     * @return {string}
     */
    feature: function()
    {
        return this._feature;
    },

    /**
     * @return {?WebInspector.TextRange}
     */
    valueRange: function()
    {
        return this._valueRange;
    },

    /**
     * @return {?number}
     */
    computedLength: function()
    {
        return this._computedLength;
    }
}


/**
 * @constructor
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!CSSAgent.CSSMedia} payload
 */
WebInspector.CSSMedia = function(cssModel, payload)
{
    this._cssModel = cssModel;
    this.text = payload.text;
    this.source = payload.source;
    this.sourceURL = payload.sourceURL || "";
    this.range = payload.range ? WebInspector.TextRange.fromObject(payload.range) : null;
    this.parentStyleSheetId = payload.parentStyleSheetId;
    this.mediaList = null;
    if (payload.mediaList) {
        this.mediaList = [];
        for (var i = 0; i < payload.mediaList.length; ++i)
            this.mediaList.push(WebInspector.CSSMediaQuery.parsePayload(payload.mediaList[i]));
    }
}

WebInspector.CSSMedia.Source = {
    LINKED_SHEET: "linkedSheet",
    INLINE_SHEET: "inlineSheet",
    MEDIA_RULE: "mediaRule",
    IMPORT_RULE: "importRule"
};

/**
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!CSSAgent.CSSMedia} payload
 * @return {!WebInspector.CSSMedia}
 */
WebInspector.CSSMedia.parsePayload = function(cssModel, payload)
{
    return new WebInspector.CSSMedia(cssModel, payload);
}

/**
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!Array.<!CSSAgent.CSSMedia>} payload
 * @return {!Array.<!WebInspector.CSSMedia>}
 */
WebInspector.CSSMedia.parseMediaArrayPayload = function(cssModel, payload)
{
    var result = [];
    for (var i = 0; i < payload.length; ++i)
        result.push(WebInspector.CSSMedia.parsePayload(cssModel, payload[i]));
    return result;
}

WebInspector.CSSMedia.prototype = {
    /**
     * @param {string} styleSheetId
     * @param {!WebInspector.TextRange} oldRange
     * @param {!WebInspector.TextRange} newRange
     */
    sourceStyleSheetEdited: function(styleSheetId, oldRange, newRange)
    {
        if (this.parentStyleSheetId !== styleSheetId)
            return;
        if (this.range)
            this.range = this.range.rebaseAfterTextEdit(oldRange, newRange);
    },

    /**
     * @param {!WebInspector.CSSMedia} other
     * @return {boolean}
     */
    equal: function(other)
    {
        if (!this.parentStyleSheetId || !this.range || !other.range)
            return false;
        return  this.parentStyleSheetId === other.parentStyleSheetId && this.range.equal(other.range);
    },

    /**
     * @return {boolean}
     */
    active: function()
    {
        if (!this.mediaList)
            return true;
        for (var i = 0; i < this.mediaList.length; ++i) {
            if (this.mediaList[i].active())
                return true;
        }
        return false;
    },

    /**
     * @return {number|undefined}
     */
    lineNumberInSource: function()
    {
        if (!this.range)
            return undefined;
        var header = this.header();
        if (!header)
            return undefined;
        return header.lineNumberInSource(this.range.startLine);
    },

    /**
     * @return {number|undefined}
     */
    columnNumberInSource: function()
    {
        if (!this.range)
            return undefined;
        var header = this.header();
        if (!header)
            return undefined;
        return header.columnNumberInSource(this.range.startLine, this.range.startColumn);
    },

    /**
     * @return {?WebInspector.CSSStyleSheetHeader}
     */
    header: function()
    {
        return this.parentStyleSheetId ? this._cssModel.styleSheetHeaderForId(this.parentStyleSheetId) : null;
    },

    /**
     * @return {?WebInspector.CSSLocation}
     */
    rawLocation: function()
    {
        if (!this.header() || this.lineNumberInSource() === undefined)
            return null;
        var lineNumber = Number(this.lineNumberInSource());
        return new WebInspector.CSSLocation(this._cssModel, this.header().id, this.sourceURL, lineNumber, this.columnNumberInSource());
    }
}

/**
 * @constructor
 * @implements {WebInspector.ContentProvider}
 * @param {!WebInspector.CSSStyleModel} cssModel
 * @param {!CSSAgent.CSSStyleSheetHeader} payload
 */
WebInspector.CSSStyleSheetHeader = function(cssModel, payload)
{
    this._cssModel = cssModel;
    this.id = payload.styleSheetId;
    this.frameId = payload.frameId;
    this.sourceURL = payload.sourceURL;
    this.hasSourceURL = !!payload.hasSourceURL;
    this.sourceMapURL = payload.sourceMapURL;
    this.origin = payload.origin;
    this.title = payload.title;
    this.disabled = payload.disabled;
    this.isInline = payload.isInline;
    this.startLine = payload.startLine;
    this.startColumn = payload.startColumn;
    if (payload.ownerNode)
        this.ownerNode = new WebInspector.DeferredDOMNode(cssModel.target(), payload.ownerNode);
}

WebInspector.CSSStyleSheetHeader.prototype = {
    /**
     * @return {!WebInspector.Target}
     */
    target: function()
    {
        return this._cssModel.target();
    },

    /**
     * @return {!WebInspector.CSSStyleModel}
     */
    cssModel: function()
    {
        return this._cssModel;
    },

    /**
     * @return {string}
     */
    resourceURL: function()
    {
        return this.isViaInspector() ? this._viaInspectorResourceURL() : this.sourceURL;
    },

    /**
     * @return {string}
     */
    _viaInspectorResourceURL: function()
    {
        var frame = this._cssModel.target().resourceTreeModel.frameForId(this.frameId);
        console.assert(frame);
        var parsedURL = new WebInspector.ParsedURL(frame.url);
        var fakeURL = "inspector://" + parsedURL.host + parsedURL.folderPathComponents;
        if (!fakeURL.endsWith("/"))
            fakeURL += "/";
        fakeURL += "inspector-stylesheet";
        return fakeURL;
    },

    /**
     * @param {number} lineNumberInStyleSheet
     * @return {number}
     */
    lineNumberInSource: function(lineNumberInStyleSheet)
    {
        return this.startLine + lineNumberInStyleSheet;
    },

    /**
     * @param {number} lineNumberInStyleSheet
     * @param {number} columnNumberInStyleSheet
     * @return {number|undefined}
     */
    columnNumberInSource: function(lineNumberInStyleSheet, columnNumberInStyleSheet)
    {
        return (lineNumberInStyleSheet ? 0 : this.startColumn) + columnNumberInStyleSheet;
    },

    /**
     * @override
     * @return {string}
     */
    contentURL: function()
    {
        return this.resourceURL();
    },

    /**
     * @override
     * @return {!WebInspector.ResourceType}
     */
    contentType: function()
    {
        return WebInspector.resourceTypes.Stylesheet;
    },

    /**
     * @param {string} text
     * @return {string}
     */
    _trimSourceURL: function(text)
    {
        var sourceURLRegex = /\n[\040\t]*\/\*[#@][\040\t]sourceURL=[\040\t]*([^\s]*)[\040\t]*\*\/[\040\t]*$/mg;
        return text.replace(sourceURLRegex, "");
    },

    /**
     * @override
     * @param {function(string)} userCallback
     */
    requestContent: function(userCallback)
    {
        this._cssModel._agent.getStyleSheetText(this.id, textCallback.bind(this))
            .catchException("")
            .then(userCallback)

        /**
         * @param {?Protocol.Error} error
         * @param {?string} text
         * @return {string}
         * @this {WebInspector.CSSStyleSheetHeader}
         */
        function textCallback(error, text)
        {
            if (error || text === null) {
                WebInspector.console.error("Failed to get text for stylesheet " + this.id + ": " + error)
                text = "";
                // Fall through.
            }
            return this._trimSourceURL(text);
        }
    },

    /**
     * @override
     */
    searchInContent: function(query, caseSensitive, isRegex, callback)
    {
        function performSearch(content)
        {
            callback(WebInspector.ContentProvider.performSearchInContent(content, query, caseSensitive, isRegex));
        }

        // searchInContent should call back later.
        this.requestContent(performSearch);
    },

    /**
     * @param {string} newText
     * @return {!Promise.<?Protocol.Error>}
     */
    _setContentPromise: function(newText)
    {
        newText = this._trimSourceURL(newText);
        if (this.hasSourceURL)
            newText += "\n/*# sourceURL=" + this.sourceURL + " */";
        return this._cssModel._agent.setStyleSheetText(this.id, newText, extractProtocolError);

        /**
         * @param {?Protocol.Error} error
         * @return {?Protocol.Error}
         */
        function extractProtocolError(error)
        {
            return error || null;
        }
    },

    /**
     * @param {string} newText
     * @param {function(?Protocol.Error)} callback
     */
    setContent: function(newText, callback)
    {
        this._setContentPromise(newText)
            .catchException(null)
            .then(callback);
    },

    /**
     * @return {boolean}
     */
    isViaInspector: function()
    {
        return this.origin === "inspector";
    }
}

/**
 * @constructor
 * @implements {CSSAgent.Dispatcher}
 * @param {!WebInspector.CSSStyleModel} cssModel
 */
WebInspector.CSSDispatcher = function(cssModel)
{
    this._cssModel = cssModel;
}

WebInspector.CSSDispatcher.prototype = {
    /**
     * @override
     */
    mediaQueryResultChanged: function()
    {
        this._cssModel.mediaQueryResultChanged();
    },

    /**
     * @override
     * @param {!CSSAgent.StyleSheetId} styleSheetId
     */
    styleSheetChanged: function(styleSheetId)
    {
        this._cssModel._fireStyleSheetChanged(styleSheetId);
    },

    /**
     * @override
     * @param {!CSSAgent.CSSStyleSheetHeader} header
     */
    styleSheetAdded: function(header)
    {
        this._cssModel._styleSheetAdded(header);
    },

    /**
     * @override
     * @param {!CSSAgent.StyleSheetId} id
     */
    styleSheetRemoved: function(id)
    {
        this._cssModel._styleSheetRemoved(id);
    },
}

/**
 * @constructor
 * @param {!WebInspector.CSSStyleModel} cssModel
 */
WebInspector.CSSStyleModel.ComputedStyleLoader = function(cssModel)
{
    this._cssModel = cssModel;
    /** @type {!Map.<!DOMAgent.NodeId, !Promise.<?WebInspector.CSSStyleDeclaration>>} */
    this._nodeIdToPromise = new Map();
}

WebInspector.CSSStyleModel.ComputedStyleLoader.prototype = {
    /**
     * @param {!DOMAgent.NodeId} nodeId
     * @return {!Promise.<?WebInspector.CSSStyleDeclaration>}
     */
    computedStylePromise: function(nodeId)
    {
        if (!this._nodeIdToPromise[nodeId])
            this._nodeIdToPromise[nodeId] = this._cssModel._agent.getComputedStyleForNode(nodeId, parsePayload.bind(this)).then(cleanUp.bind(this));

        return this._nodeIdToPromise[nodeId];

        /**
         * @param {?Protocol.Error} error
         * @param {!Array.<!CSSAgent.CSSComputedStyleProperty>} computedPayload
         * @return {?WebInspector.CSSStyleDeclaration}
         * @this {WebInspector.CSSStyleModel.ComputedStyleLoader}
         */
        function parsePayload(error, computedPayload)
        {
            return !error && computedPayload ? WebInspector.CSSStyleDeclaration.parseComputedStylePayload(this._cssModel, computedPayload) : null;
        }

        /**
         * @param {?WebInspector.CSSStyleDeclaration} computedStyle
         * @return {?WebInspector.CSSStyleDeclaration}
         * @this {WebInspector.CSSStyleModel.ComputedStyleLoader}
         */
        function cleanUp(computedStyle)
        {
            delete this._nodeIdToPromise[nodeId];
            return computedStyle;
        }
    }
}

/**
 * @param {!WebInspector.Target} target
 * @return {?WebInspector.CSSStyleModel}
 */
WebInspector.CSSStyleModel.fromTarget = function(target)
{
    if (!target.isPage())
        return null;
    return /** @type {?WebInspector.CSSStyleModel} */ (target.model(WebInspector.CSSStyleModel));
}

/**
 * @param {!WebInspector.DOMNode} node
 * @return {!WebInspector.CSSStyleModel}
 */
WebInspector.CSSStyleModel.fromNode = function(node)
{
    return /** @type {!WebInspector.CSSStyleModel} */ (WebInspector.CSSStyleModel.fromTarget(node.target()));
}

/**
 * @constructor
 * @param {?Array.<!WebInspector.CSSRule>} matchedRules
 * @param {?Array.<!WebInspector.CSSStyleModel.InheritedMatches>} inherited
 * @param {?Array.<!WebInspector.CSSStyleModel.PseudoElementMatches>} pseudoElements
 */
WebInspector.CSSStyleModel.MatchedStyleResult = function(matchedRules, inherited, pseudoElements)
{
    this.matchedCSSRules = matchedRules;
    this.inherited = inherited;
    this.pseudoElements = pseudoElements;
}

/**
 * @constructor
 * @param {number} pseudoId
 * @param {?Array.<!WebInspector.CSSRule>} rules
 */
WebInspector.CSSStyleModel.PseudoElementMatches = function(pseudoId, rules)
{
    this.pseudoId = pseudoId;
    this.rules = rules;
}

/**
 * @constructor
 * @param {?WebInspector.CSSStyleDeclaration} inlineStyle
 * @param {?Array.<!WebInspector.CSSRule>} matchedRules
 */
WebInspector.CSSStyleModel.InheritedMatches = function(inlineStyle, matchedRules)
{
    this.inlineStyle = inlineStyle;
    this.matchedCSSRules = matchedRules;
}

/**
 * @constructor
 * @param {?WebInspector.CSSStyleDeclaration} inlineStyle
 * @param {?WebInspector.CSSStyleDeclaration} attributesStyle
 */
WebInspector.CSSStyleModel.InlineStyleResult = function(inlineStyle, attributesStyle)
{
    this.inlineStyle = inlineStyle;
    this.attributesStyle = attributesStyle;
}

