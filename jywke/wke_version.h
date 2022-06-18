#pragma once

#define ___VER_1(_major, _minor, _build) L#_major##"_"###_minor##"_"###_build
#define ___VER_2(_major, _minor, _build) L#_major##"."###_minor##"."###_build
#define ___VER_3(_major, _minor, _build) ___VER_1(_major, _minor, _build)
#define ___VER_4(_major, _minor, _build) ___VER_2(_major, _minor, _build)

#define WKE_MAJORVERSION               1       // ֧�ֿ����汾��
#define WKE_MINORVERSION               7       // ֧�ֿ�ΰ汾��
#define WKE_BUILDVERSION               618     // ֧�ֿ����汾��
#define WKE_VERSION                    ___VER_4(WKE_MAJORVERSION, WKE_MINORVERSION, WKE_BUILDVERSION)    // ֧�ֿ�汾��
#define WKE_VERSION_                   ___VER_3(WKE_MAJORVERSION, WKE_MINORVERSION, WKE_BUILDVERSION)    // ֧�ֿ�汾��, �㻻���»��� x_x_xxx
