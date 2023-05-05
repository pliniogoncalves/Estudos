*** Settings ***
Library    SeleniumLibrary

*** Variables ***
#My test data
${SongName}    Soad B.Y.O.B

#configuration variables
${URL}        https://www.youtube.com/
${Browser}    chrome   

#Elements
${Input_Search}      //input[@id="search"]
${Button_Search}     //button[@id="search-icon-legacy"]
${First}            (//yt-formatted-string[@class="style-scope ytd-video-renderer"])[1]
${Test}             (//yt-formatted-string[@class="style-scope ytd-watch-metadata"])[1]
*** Keywords ***
Given that I access the youtube website
    Open Browser    ${URL}    ${Browser}

When i type the name of the sonclick on the first option in the listg
    Input Text    ${Input_Search}    ${SongName}

And click on the search button
    Click Element    ${Button_Search}

And click on the first option in the list
    Wait Until Element Is Visible    ${First}    10  
    Click Element                    ${First}

Then the video is played
    Wait Until Element Is Visible    ${Test}    10
    Element Should Be Visible        ${Test}
    Sleep                             10s
    Close Browser


*** Test Cases ***
Scenario 1: Play video on youtube website
    Given that I access the youtube website
    When i type the name of the sonclick on the first option in the listg
    And click on the search button
    And click on the first option in the list
    Then the video is played
