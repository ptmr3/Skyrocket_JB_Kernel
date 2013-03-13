/*
#include <linux/module.h>
#define EVENT_CHANNEL		"APPS_RIVA_BT_CMD"
#define HCI_REGISTER_SET		0
static int hcismd_set;
static int hcismd_set_enable(const char *val, struct kernel_param *kp);
static void hci_dev_smd_open(struct work_struct *worker);
static void hci_dev_restart(struct work_struct *worker);
struct hci_smd_data {
/* Rx queue monitor timer function */
	if (list == (struct sk_buff *)list_) {
static void release_lock(void)
/* Rx timer callback function */
	if (is_rx_q_empty(arg) && wake_lock_active(&hs.wake_lock_rx)) {
static int hci_smd_open(struct hci_dev *hdev)


static void hci_smd_recv_data(void)
	len = smd_read_avail(hsmd->data_channel);
	if (len <= 0)
	rc = smd_read(hsmd->data_channel, skb_put(skb, len), len);
	skb->dev = (void *)hsmd->hdev;
	rc = hci_recv_frame(skb);
	/*
out_data:
static void hci_smd_recv_event(void)
	len = smd_read_avail(hsmd->event_channel);
	while (len > 0) {
		rc = smd_read(hsmd->event_channel, skb_put(skb, len), len);
		skb->dev = (void *)hsmd->hdev;
		skb_orphan(skb);
		rc = hci_recv_frame(skb);
		len = smd_read_avail(hsmd->event_channel);
static int hci_smd_send_frame(struct sk_buff *skb)
	kfree_skb(skb);
static void hci_smd_rx(unsigned long arg)
static void hci_smd_notify_event(void *data, unsigned int event)

	int len = 0;
	if (!hdev) {
	switch (event) {
		break;
		if (!open_worker) {
			BT_ERR("Out of memory");
			break;
		}
		INIT_WORK(open_worker, hci_dev_smd_open);
		schedule_work(open_worker);
		break;
static void hci_smd_notify_data(void *data, unsigned int event)
	switch (event) {

	}
static int hci_smd_hci_register_dev(struct hci_smd_data *hsmd)
{
	struct hci_dev *hdev;


	if (hci_register_dev(hdev) < 0) {
		BT_ERR("Can't register HCI device");
		hci_free_dev(hdev);
		hsmd->hdev = NULL;
		return -ENODEV;
	}
	return 0;
}
static int hci_smd_register_smd(struct hci_smd_data *hsmd)
{
	int rc;
        /* Initialize and register HCI device */

		return -ENODEV;
	rc = smd_named_open_on_edge(DATA_CHANNEL, SMD_APPS_WCNSS,
		return -ENODEV;
	/* Disable the read interrupts on the channel */
static void hci_smd_deregister_dev(struct hci_smd_data *hsmd)
		hci_free_dev(hsmd->hdev);
	smd_close(hs.event_channel);
	if (wake_lock_active(&hs.wake_lock_rx))
	/*Destroy the timer used to monitor the Rx queue for emptiness */
static void hci_dev_restart(struct work_struct *worker)
	mutex_unlock(&hci_smd_enable);
	kfree(worker);
}

static void hci_dev_smd_open(struct work_struct *worker)
{
	mutex_lock(&hci_smd_enable);
	hci_smd_hci_register_dev(&hs);
	mutex_unlock(&hci_smd_enable);
static int hcismd_set_enable(const char *val, struct kernel_param *kp)
	mutex_lock(&hci_smd_enable);
	ret = param_set_int(val, kp);
	if (ret)
	switch (hcismd_set) {
	case 1:
	break;
done:
static void __exit hci_smd_exit(void)
MODULE_AUTHOR("Ankur Nandwani <ankurn@codeaurora.org>");