## Hash-Table Maps

```c
#define IPV4_FAMILY 1
struct ip_key {
	union {
		__u32 v4_addr;
		__u8 v6_addr[16];
	};
	__u8 family;
};

struct bpf_map_def SEC("maps") counters = {
	.type = BPF_MAP_TYPE_HASH,
	.key_size = sizeof(struct ip_key),
	.value_size = sizeof(uint64_t),
	.max_entries = 100,
	.map_flags = BPF_F_NO_PREALLOC
};

uint64_t update_counter(uint32_t ipv4)
{
	uint64_t value;
	struct ip_key key = {};

	key.v4_addr = ip4;
	key.family = IPV4_FAMILY;
	bpf_map_lookup_elem(counters, &key ,&value);
	(*value) += 1 ;
}

```

## Array Maps

## Program Array Maps

```c
struct bpf_map_def SEC("maps") programs = {
	.type = BPF_MAP_TYPE_PROG_ARRAY,
	.key_size = 4,
	.value_size = 4,
	.max_entries = 1024,
};

int key = 1;
struct bpf_insn prog [] = {
	BPF_MOV64_IMM(BPF_REG_0 , 0),
	BPF_EXIT_INSN(),
};
prog_fd = bpf_prog_load(BPF_PROG_TYPE_KPROBE ,prog ,sizeof(prog), "GPL");
bpf_map_update_elem(&programs, &key, &prog_fd, BPF_ANY);

SEC("kprobe/seccomp_phase1")
int bpf_kprobe_program ( struct pt_regs * ctx)
{
	int key = 1 ;

	/* dispatch into next BPF program */
	bpf_tail_call(ctx, &programs, &key);

	/* fall through when the program descriptor is not in the map */
	char fmt[] = "missing program in prog_array map \n";

	bpf_trace_printk(fmt ,sizeof(fmt));

	return 0 ;
}

```

## Perf Events Array Maps

## Per-CPU Hash Maps

## Per-CPU Array Maps

## Stack Trace Maps



