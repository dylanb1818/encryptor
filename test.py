import subprocess

test_cases = [{'input': 'check', 'output': '1'}]

for test in test_cases:
    input_value = test['input']
    expected_output = test['output']
    process = subprocess.Popen(['./program'], 
                               stdin=subprocess.PIPE, 
                               stdout=subprocess.PIPE, 
                               stderr=subprocess.PIPE)
    
    stdout, _ = process.communicate(input=input_value.encode())
    actual_output = stdout.decode().strip()
    print('-------')
    print(actual_output)
    print('-------')

    if actual_output == expected_output:
        print('Test case passed')
    
    else:
        print('Test case failed')
        print('Expected:', expected_output)
        print(actual_output)
