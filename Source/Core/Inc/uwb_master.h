/*
 * ss_twr_responder.h
 *
 *  Created on: Aug 9, 2022
 *      Author: auabe
 */

#ifndef INC_UWB_MASTER_H_
#define INC_UWB_MASTER_H_

#include <stdint.h>

int uwb_master(void);
void set_tx_param(uint8_t parameter);

#endif /* INC_UWB_MASTER_H_ */
