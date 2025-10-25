#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#include "gatsby_contents.h"

static int major;

MODULE_AUTHOR("Timo Alejandro Aranjo <alex.aranjo@gmail.com>");
MODULE_DESCRIPTION("A driver that endlessly outputs the text of The Great Gatsby in a loop on a character device.");
MODULE_LICENSE("GPL");

static ssize_t gatsby_read (struct file * file, char __user * buf, size_t length, loff_t * offset) {
    return 0;
}

static ssize_t gatsby_write (struct file * file, const char __user * buf, size_t length, loff_t * offset) {
    return length;
}

static int gatsby_open (struct inode * inode, struct file * file) {
    printk(KERN_INFO "gatsby: File was opened");

    return 0;
}

static int gatsby_release (struct inode * inode, struct file * file) {
    printk(KERN_INFO "gatsby: File was closed");

    return 0;
}

struct file_operations fops = {
    .read=gatsby_read,
    .write=gatsby_write,
    .open=gatsby_open,
    .release=gatsby_release
};

static int __init gatsby_init(void) {
    major = register_chrdev(0, "gatsby", &fops);
    
    if (major < 0) {
        printk(KERN_ERR "gatsby: Could not obtain a dynamic major number.");
        return major;
    }
    
    printk(KERN_INFO "gatsby: Major number obtained (%d)", major);
        
    printk(KERN_INFO "gatsby: Driver inserted into kernel."); 
    
    return 0;
}

static int __exit gatsby_exit(void) { 
    unregister_chrdev(major, "gatsby");
    
    printk(KERN_INFO "gatsby: Driver removed from kernel.");
    
    return 0;
}

module_init(gatsby_init);
module_exit(gatsby_exit);
