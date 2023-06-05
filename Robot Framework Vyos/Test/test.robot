*** Settings ***
Library    SSHLibrary

*** Variables ***
${HOST1}          192.168.0.124
${HOST2}          192.168.0.94
${USERNAME}      vyos
${PASSWORD}      vyos

*** Test Cases ***
Ping Test HOST1 - HOST2
    Open Connection    ${HOST1}
    Login             ${USERNAME}    ${PASSWORD}
    ${output}=    Execute Command    ping -c 5 ${HOST2}
    Log               ${output}
     Should Contain    ${output}    5 packets transmitted, 5 received, 0% packet loss
    Close Connection

Ping Test HOST2 - HOST1
    Open Connection    ${HOST2}
    Login             ${USERNAME}    ${PASSWORD}
    ${output}=    Execute Command    ping -c 5 ${HOST1}
    Log               ${output}
     Should Contain    ${output}    5 packets transmitted, 5 received, 0% packet loss
    Close Connection

