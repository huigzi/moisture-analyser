/**
 * \file   nettask.h
 *
 *  \brief  This file contains the network task.
 *
 *  (C) Copyright 2013, gooao, Inc
 *
 */

#ifndef _GUAO_NETWORK_H_
#define _GUAO_NETWORK_H_

#include <stdio.h>
#include <netmain.h>
#include <_stack.h>

#ifdef __cplusplus
extern "C"
{
#endif

void	tskTcpServer();
void	tskTcpClient();

#ifdef __cplusplus
}
#endif

#endif /* _GUAO_NETWORK_H_*/
/* ========================================================================== */
/*                              END OF FILE                                   */
/* ========================================================================== */
