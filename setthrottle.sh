for i in `seq 0 27`; do
    sudo cpufreq-set -g performance -c $i
done

echo "1" | sudo tee  /sys/devices/system/cpu/intel_pstate/no_turbo