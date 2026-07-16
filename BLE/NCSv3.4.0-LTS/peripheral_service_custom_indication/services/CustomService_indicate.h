#ifndef INCLUDE_CUSTOM_SERVICE_INDICATE_H_
#define INCLUDE_CUSTOM_SERVICE_INDICATE_H_

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/conn.h>

void CustomService_indicate_send(struct bt_conn *conn, uint8_t *data);

#endif /* INCLUDE_CUSTOM_SERVICE_NOTIFY_H_ */