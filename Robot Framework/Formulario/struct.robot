*** Settings ***
Library    SeleniumLibrary

*** Variables ***
${BROWSER}             chrome
${input_name}          id:name
${input_phone}         id:phone
${input_email}         id:email 
${input_password}      id:password 
${textarea_address}    id:address 
${button_submit}       name:submit

*** Keywords ***
open browser and access the website
    Open Browser    https://itera-qa.azurewebsites.net/home/automation    ${BROWSER}

fill in fields
    Input Text    ${input_name}            Plinio
    Input Text    ${input_phone}           988557799
    Input Text    ${input_email}           Plinio@teste.com
    Input Text    ${input_password}        123456
    Input Text    ${textarea_address}      xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    Input Text    ${input_name}            Plinio

click submit
    Click Element    ${button_submit}

close website
    Close Browser

*** Test Cases ***
scenario 1: Test fill out form
    open browser and access the website
    fill in fields
    click submit
    close website
    

