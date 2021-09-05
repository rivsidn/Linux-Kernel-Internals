#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("proc fs test demo");

static char *name = NULL;
static int test_proc_show(struct seq_file *s,void *v)
{
    
	seq_printf(s,"test :%s",name);
	return 0;
}
static int test_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file,test_proc_show,NULL);

}

static ssize_t test_proc_write(struct file *file, const char __user *buf, size_t count,loff_t *f_ops)
{
    char *buffer = NULL;
    buffer = kzalloc(count+1,GFP_KERNEL);
    if(buffer == NULL)
	return -1;

    if(copy_from_user(buffer,buf,count))
    {
    	kfree(buffer);
	return -1;
    }
    printk("proc test demo write value %s\n",buffer);
    if(name != NULL)
        kfree(name);
    name = buffer;
    return count;
}


static const struct file_operations test_proc_fops = {
	.open = test_proc_open,
	.read = seq_read,
	.write = test_proc_write,
	.llseek = seq_lseek,
	.release = single_release,

};
static int proc_test_init(void)
{
    proc_create("proc_test_demo",S_IWUSR|S_IRUGO,NULL,&test_proc_fops);
    return 0;
}

static void proc_test_exit(void)
{
   remove_proc_entry("proc_test_demo",NULL); 
   if(name != NULL)
	kfree(name);
   return ;
}
module_init(proc_test_init);
module_exit(proc_test_exit);






