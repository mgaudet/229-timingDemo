for i in `seq 0 27`; do
    sudo cpufreq-set -g powersave -c $i
done

echo "0" | sudo tee  /sys/devices/system/cpu/intel_pstate/no_turbo