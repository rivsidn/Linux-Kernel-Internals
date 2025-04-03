
# 遍历进程的vma结构体
# $arg0:  要遍历的task_struct 结构体地址
define traverse_task_vma
	set $total = 0
	set $mm = ((struct task_struct *)$arg0)->mm

	set $vma = $mm->mmap
	while ($vma)
		set $total = $total + 1

		printf "%p %lx - %lx\n", $vma, $vma->vm_start, $vma->vm_end
		set $vma = ((struct vm_area_struct *)$vma)->vm_next
	end
	printf "total %d\n", $total
end


