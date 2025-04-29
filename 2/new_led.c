#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/leds.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/of.h>

#define LED_OFF	0
#define LED_ON	1

struct drvled_data {
	struct gpio_desc *desc;
	struct led_classdev led_cdev;
};

static struct drvled_data *drvled_data;

static void drvled_setled(unsigned int status)
{
	if (status == LED_ON)
		gpiod_set_value(drvled_data->desc, 1);
	else
		gpiod_set_value(drvled_data->desc, 0);
}

static void drvled_change_state(struct led_classdev *led_cdev,
				enum led_brightness brightness)
{
	drvled_setled(brightness ? LED_ON : LED_OFF);
}

static int drvled_probe(struct platform_device *pdev)
{
	int result;

	/* 
	 * Allocate memory for driver data
	 * */
	drvled_data = devm_kzalloc(&pdev->dev, sizeof(*drvled_data), GFP_KERNEL);
	if (!drvled_data)
		return -ENOMEM;

	/* 
	 * Get GPIO descriptor from Device Tree 
	 * */
	drvled_data->desc = devm_gpiod_get(&pdev->dev, "led", GPIOD_OUT_LOW);
	if (IS_ERR(drvled_data->desc)) {
		dev_err(&pdev->dev, "Failed to get GPIO descriptor\n");
		return PTR_ERR(drvled_data->desc);
	}

	/* 
	 * Initialize LED class device 
	 * */
	drvled_data->led_cdev.name = "rpi_led";
	drvled_data->led_cdev.brightness_set = drvled_change_state;

	/* 
	 * Register LED class device 
	 * */
	result = devm_led_classdev_register(&pdev->dev, &drvled_data->led_cdev);
	if (result) {
		dev_err(&pdev->dev, "Error registering LED device\n");
		return result;
	}

	dev_info(&pdev->dev, "LED driver initialized.\n");
	return 0;
}

static int drvled_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "LED driver removed.\n");
	return 0;
}

static const struct of_device_id drvled_dt_ids[] = {
	{ .compatible = "rpi,led" },
	{ }
};
MODULE_DEVICE_TABLE(of, drvled_dt_ids);

static struct platform_driver drvled_driver = {
	.driver = {
		.name = "drvled",
		.of_match_table = drvled_dt_ids,
	},
	.probe = drvled_probe,
	.remove = drvled_remove,
};

module_platform_driver(drvled_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mihir");
MODULE_DESCRIPTION("Raspberry Pi 4B LED Driver");
MODULE_VERSION("3.0");

