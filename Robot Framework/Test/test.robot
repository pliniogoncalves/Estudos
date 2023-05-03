*** Settings ***
Library    SeleniumLibrary

*** Variables ***
${BROWSER}    chrome

*** Keywords ***
open google website
    Open Browser    https://www.google.com.br/    ${BROWSER}

close website
    Close Browser

open globo website
    Open Browser    https://g1.globo.com/    ${BROWSER}
    
*** Test Cases ***
scenario 1: Test open google website
    open google website
    close website
    
scenario 2: Test open globo website
    open globo website
    Close Browser