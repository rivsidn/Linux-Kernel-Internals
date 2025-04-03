
define smp_processor_id
	set $thread_info = (struct thread_info *)((unsigned long)$rsp & ~(8192 - 1))

	printf "%d\n", $thread_info->cpu
end

define get_current
	set $thread_info = (struct thread_info *)((unsigned long)$rsp & ~(8192 - 1))
	set $cpu = $thread_info->cpu

	printf "%p\n", cpu_pda[$cpu].pcurrent
end

define show_current_name
	set $thread_info = (struct thread_info *)((unsigned long)$rsp & ~(8192 - 1))
	set $cpu = $thread_info->cpu

	printf "%s\n", (cpu_pda[$cpu].pcurrent)->comm
end

define traverse_tasks
	set $task_list = init_task.tasks.next
	while ($task_list != &(init_task.tasks))
		set $task_struct = (struct task_struct *)((char *)$task_list - \
				   (long)&((struct task_struct *)0)->tasks)
		printf "%p %4d %s\n", $task_struct, $task_struct->pid, $task_struct->comm
		set $task_list = $task_struct->tasks.next
	end
end

define find_task_by_pid
	set $task_list = init_task.tasks.next
	while ($task_list != &(init_task.tasks))
		set $task_struct = (struct task_struct *)((char *)$task_list - \
				   (long)&((struct task_struct *)0)->tasks)
		if ($task_struct->pid == $arg0)
			printf "%p\n", $task_struct
		end
		set $task_list = $task_struct->tasks.next
	end
end
