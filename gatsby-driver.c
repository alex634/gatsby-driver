#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#include "gatsby_contents.h"

static int major;

MODULE_AUTHOR("Timo Alejandro Aranjo <alex.aranjo@gmail.com>");
MODULE_DESCRIPTION("A driver that endlessly outputs the text of The Great Gatsby in a loop on a character device.");
MODULE_LICENSE("GPL");

static ssize_t gatsby_read (struct file * file, char __user * buf, size_t length, loff_t * offset) {
    size_t copied = 0;
    
    while (copied < length) {
    
        if (length - copied > text_length - (*offset % text_length)) {
            unsigned long ret = (text_length - (*offset % text_length)) - copy_to_user(buf + copied, (const void *)(text + (*offset % text_length)), text_length - (*offset % text_length));
            
            copied += ret;
            *offset += ret;
        } else {
            unsigned long ret = (length - copied) - copy_to_user(buf + copied, (const void *)(text + (*offset % text_length)), length - copied);
            
            copied += ret;
            *offset += ret;
        }
    }
    
    return copied;
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

static void __exit gatsby_exit(void) { 
    unregister_chrdev(major, "gatsby");
    
    printk(KERN_INFO "gatsby: Driver removed from kernel.");
}

module_init(gatsby_init);
module_exit(gatsby_exit);
