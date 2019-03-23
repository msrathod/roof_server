/*
 *
 * roof_cmd.h: CMD defines for roof server
 *                 
 */

#ifndef ROOF_CMD_H
#define ROOF_CMD_H

#ifdef __cplusplus
extern "C" {
#endif

enum Cmd_Alias
{
	CMD_NONE		    = 0x00,
	CMD_OPEN		    ,
	CMD_CLOSE		    ,
	CMD_STATE_CHECK     ,
    CMD_STOP            ,

	CMD_GET_TEMP_AMB   	= 0x20,
	CMD_GET_HUMD_AMB 	,
	CMD_GET_TEMP_ONION	,
    CMD_GET_RAIN_SENSE  ,

    CMD_RUN_FANS        = 0x40,
	CMD_STOP_FANS       ,

	CMD_CAPTURE		    = 0x60,
	CMD_GET_IMAGE		,
};

#ifdef __cplusplus
}
#endif
#endif // ROOF_CMD_H