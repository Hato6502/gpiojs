#include <linux/kernel.h>
#include <linux/input.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>

MODULE_AUTHOR("hato6502");
MODULE_DESCRIPTION("The button device driver as joystick.");
MODULE_LICENSE("GPL");

#define BUTTONGPIO_NULL 0xffffffff

typedef const struct{
	unsigned int gpio;
	int key;
}ButtonNode;

#include "config.c"

struct input_dev *dev;

void timeout(unsigned long unused){
	ButtonNode *button;

	mod_timer(&(dev->timer),jiffies + HZ/60);

        for(button = buttonList;button->gpio != BUTTONGPIO_NULL;button++){
	        input_report_key(dev,button->key,gpio_get_value(button->gpio));
        }

        input_sync(dev);
}

int init_module(){
	ButtonNode *button;

	dev = input_allocate_device();

	dev->name = "button";
	dev->phys = "A/Fake/Path";
	dev->id.vendor = 0x0001;
	dev->id.product = 0x0001;
	dev->id.version = 0x0100;

	set_bit(EV_KEY,dev->evbit);

        for(button = buttonList;button->gpio != BUTTONGPIO_NULL;button++){
	        if (gpio_request(button->gpio,"button")){
                        printk(KERN_ALERT "Couldn't allocate gpio. \n");
                        return -1;
                }

                if (gpio_direction_input(button->gpio)){
                        printk(KERN_ALERT "Couldn't set gpio direction. \n");
                        return -1;
                }

		set_bit(button->key,dev->keybit);
        }

	if(input_register_device(dev)){
                printk(KERN_ALERT "Couldn't register device. \n");
		return -1;
	}

	init_timer(&(dev->timer));
	dev->timer.function = timeout;
	dev->timer.expires = jiffies + HZ;
	add_timer(&(dev->timer));

	return 0;
}

void cleanup_module(){
	ButtonNode *button;

        for(button = buttonList;button->gpio != BUTTONGPIO_NULL;button++){
	        gpio_free(button->gpio);
        }

	input_unregister_device(dev);
}
