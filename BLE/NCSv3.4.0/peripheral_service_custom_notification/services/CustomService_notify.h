#ifndef INCLUDE_CUSTOM_SERVICE_NOTIFY_H_
#define INCLUDE_CUSTOM_SERVICE_NOTIFY_H_

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/conn.h>

void CustomService_notify_send(struct bt_conn *conn, uint8_t *data, uint16_t len);

#endif /* INCLUDE_CUSTOM_SERVICE_NOTIFY_H_ */
