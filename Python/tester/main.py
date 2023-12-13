import os
import subprocess

program_path = '../../cmake-build-release/PEA_PROJ_2.exe'
result_file = 'result.txt'
ftv55 = '../../RESOURCES/ftv55.atsp'
ftv170 = '../../RESOURCES/ftv170.atsp'
rbg358 = '../../RESOURCES/rbg358.atsp'


def run_program(name, params):
    results = ''
    for i in range(10):
        subprocess.run(params)
        with open(result_file, 'r') as f:
            results += f.readline() + '\n'
    with open('../tests_results/' + name, 'w') as f:
        f.write(results)


def sa_greedy_55():
    run_program('sa_greedy_55', [program_path, 'SA', ftv55, '1', '2', '0.05', '1', '0.999'])


# def sa_random_55():
#     run_program('sa_random_55', [program_path, 'SA', ftv55, '0', '2', '0.5', '1', '0.995'])


def sa_greedy_170():
    run_program('sa_greedy_170', [program_path, 'SA', ftv170, '1', '4', '0.0000001', '0.5', '0.999'])


# def sa_random_170():
#     run_program('sa_random_170', [program_path, 'SA', ftv170, '0', '4', '0.2', '0.5', '0.995'])


def sa_greedy_358():
    run_program('sa_greedy_358', [program_path, 'SA', rbg358, '1', '6', '0.0005', '0.5', '0.995'])


# def sa_random_358():
#     run_program('sa_random_358', [program_path, 'SA', rbg358, '0', '6', '0.2', '0.5', '0.995'])


def ts_greedy_55():
    run_program('ts_greedy_55', [program_path, 'TS', ftv55, '1', '2', '10000'])


# def ts_random_55():
#     run_program('ts_random_55', [program_path, 'TS', ftv55, '0', '2', '1000'])


def ts_greedy_170():
    run_program('ts_greedy_170', [program_path, 'TS', ftv170, '1', '4', '10000'])


# def ts_random_170():
#     run_program('ts_random_170', [program_path, 'TS', ftv170, '0', '4', '1000'])


def ts_greedy_358():
    run_program('ts_greedy_358', [program_path, 'TS', rbg358, '1', '6', '5000'])


# def ts_random_358():
#     run_program('ts_random_358', [program_path, 'TS', rbg358, '0', '6', '1000'])


# sa_random_55()
# sa_greedy_55()
# sa_random_170()
# sa_greedy_170()
# sa_random_358()
# sa_greedy_358()
#
# ts_random_55()
# ts_greedy_55()
# ts_random_170()
ts_greedy_170()
# ts_random_358()
ts_greedy_358()