/* The part of ahi.device's interface this game uses (AHI V4 and later):
 * the device name, the unit and the IO request of CMD_WRITE. Layout as
 * AHI's developer files document it. GPL 3 or later. */
#ifndef DEVICES_AHI_H
#define DEVICES_AHI_H

#include <exec/types.h>
#include <exec/io.h>

typedef LONG Fixed;

#define AHINAME          "ahi.device"
#define AHI_DEFAULT_UNIT (0U)
#define AHI_NO_UNIT      (255U)

#define AHIST_M8S  (0UL)
#define AHIST_M16S (1UL)
#define AHIST_S8S  (2UL)
#define AHIST_S16S (3UL)

struct AHIRequest {
	struct IOStdReq    ahir_Std;
	UWORD              ahir_Version;
	UWORD              ahir_Pad1;
	ULONG              ahir_Private[2];
	ULONG              ahir_Type;
	ULONG              ahir_Frequency;
	Fixed              ahir_Volume;
	Fixed              ahir_Position;
	struct AHIRequest *ahir_Link;
};

#endif
