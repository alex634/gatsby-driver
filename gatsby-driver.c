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
    size_t normalized_offset = *offset % text_length;

    while (copied < length) {
        //< Amount left to copy from current offset in source buffer 
        //> Remaining bytes necessary to copy to the user buffer
        if (text_length - normalized_offset < length - copied) {
            copy_to_user(buf, (const void *)(text + normalized_offset), text_length - normalized_offset);
            copied += text_length - normalized_offset;
            normalized_offset = 0;

        } else {
            copy_to_user(buf, (const void *)(text + normalized_offset), length - copied);
            copied += length - copied;
            normalized_offset += length - copied;
        } 
    }

    return length;
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
