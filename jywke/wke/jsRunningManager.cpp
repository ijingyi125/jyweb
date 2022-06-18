#include <Windows.h>
#include "jsRunningManager.h"


jsValue jsRunningManager::GetValue(const char* prop, jsValue obj)
{
    if (NULL == obj)
        return jsGetGlobal(GetJsExec(), prop);
    else
        return jsGet(GetJsExec(), obj, prop);
}

ValueType jsRunningManager::jsValue2ValueType(jsValue val)
{
    jsType type = jsTypeOf(val);
    ValueType vt;
    switch (type)
    {
    case JSTYPE_STRING:
        vt.param.str = jsToString(GetJsExec(), val);
        vt.type = ValueType::TEXT;
        break;
    case JSTYPE_BOOLEAN:
        vt.param.boolean = jsIsTrue(val);
        vt.type = ValueType::BOOL;
        break;
    case JSTYPE_NUMBER:
        vt.param.number = jsToDouble(GetJsExec(), val);
        vt.type = ValueType::DOUBULE;
        break;

    default:
        vt.param.number = 0;
        vt.type = ValueType::TEXT;
        break;
    }
    return vt;
}

jsValue jsRunningManager::CallJsFunc(const char* funcName, ValueType* params, int argCount, jsValue obj)
{
    jsValue jsFunc;
    if (NULL == obj)
        jsFunc = jsGetGlobal(GetJsExec(), funcName);
    else
        jsFunc = jsGet(GetJsExec(), obj, funcName);

    jsValue* jsArgs = NULL;
    if (argCount > 0)
    {
        jsArgs = new jsValue[argCount];
        for (int i = 0; i < argCount; i++)
        {
            switch (params[i].type)
            {
            case ValueType::ArgType::TEXT:
                jsArgs[i] = jsString(GetJsExec(), params[i].param.str);
                break;
            case ValueType::ArgType::INT:
                jsArgs[i] = jsInt(params[i].param.num);
                break;
            case ValueType::ArgType::DOUBULE:
                jsArgs[i] = jsDouble(params[i].param.number);
                break;
            case ValueType::ArgType::BOOL:
                jsArgs[i] = jsBoolean(params[i].param.boolean);
                break;
            }
        }
    }

    jsValue ret = NULL;
    if (NULL == obj)
    {
        ret = jsCallGlobal(GetJsExec(), jsFunc, jsArgs, argCount);
    }
    else
    {
        ret = jsCall(GetJsExec(), jsFunc, obj, jsArgs, argCount);
    }
    if (jsArgs)
        delete[]jsArgs;
    return ret;
}