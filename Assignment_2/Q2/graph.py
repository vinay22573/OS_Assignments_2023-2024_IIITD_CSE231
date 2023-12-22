import matplotlib.pyplot as plt
with open('custom_execution_times.txt', 'r') as file:
    lines = file.readlines()
custom_execution_times_sched_other = []
custom_execution_times_sched_rr = []
custom_execution_times_sched_fifo = []
for line in lines:
    if "Process 1 (SCHED_OTHER)" in line:
        custom_execution_times_sched_other.append(float(line.split()[-1]))
    elif "Process 2 (SCHED_RR)" in line:
        custom_execution_times_sched_rr.append(float(line.split()[-1]))
    elif "Process 3 (SCHED_FIFO)" in line:
        custom_execution_times_sched_fifo.append(float(line.split()[-1]))
plt.figure(figsize=(12, 6))
plt.hist(custom_execution_times_sched_other, bins=10, color='blue', alpha=0.7, label='SCHED_OTHER_Process A')
plt.hist(custom_execution_times_sched_rr, bins=10, color='green', alpha=0.7, label='SCHED_RR_Process B')
plt.hist(custom_execution_times_sched_fifo, bins=10, color='red', alpha=0.7, label='SCHED_FIFO_Process C')
plt.xlabel('Execution Time (s)')
plt.ylabel('Frequency')
plt.title('Execution Time Histogram')
plt.grid(True)
plt.legend()
for i, val in enumerate(custom_execution_times_sched_other):
    plt.text(val, i, f'A: {val:.2f}', color='blue', va='center', fontsize=8, fontweight='bold')
for i, val in enumerate(custom_execution_times_sched_rr):
    plt.text(val, i, f'B: {val:.2f}', color='green', va='center', fontsize=8, fontweight='bold')
for i, val in enumerate(custom_execution_times_sched_fifo):
    plt.text(val, i, f'C: {val:.2f}', color='red', va='center', fontsize=8, fontweight='bold')
plt.show()
