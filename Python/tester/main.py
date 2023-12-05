import os
import subprocess

program_path = '../../cmake-build-release/PEA_PROJ_2.exe'
result_file = 'result.txt'
file = '../../RESOURCES/ftv55.atsp'
time_limit_minutes = '2'

tau_list = ['0.2', '0.5', '0.7', '0.9']
inner_loop_factor_list = ["1.0", '0.75', '0.5', '0.25']
cooling_factor_list = ["0.9", '0.95', '0.99', '0.995', '0.999', '0.9995', '0.9999']

results = 'TAU;INNER_LOOP;COOLING_FACTOR;RESULT;TIME_EXCEEDED\n'

for tau in tau_list:
    for inner_loop_factor in inner_loop_factor_list:
        for cooling_factor in cooling_factor_list:
            subprocess.run([program_path, file, time_limit_minutes, tau, inner_loop_factor, cooling_factor])
            with open(result_file, 'r') as f:
                line = f.readline().split(' ')
                results += '{};{};{};{};{}'.format(tau, inner_loop_factor, cooling_factor, line[0], line[1])

with open('../tests_results/tests_result_358_05_12_2023', 'w') as f:
    f.write(results)
