*** Settings ***
Resource    ../../Resource/settings.resource
Resource    ../../Elements/Main_Elements.resource

*** Keywords ***
When I perform a round-trip flight search
    Wait Until Element Is Visible  ${Home.a_voos}           10
    Click Element                  ${Home.a_voos}
    Wait Until Element Is Visible  ${Voo.Input_IdaeVolta}  10
    Click Element                  ${Voo.Input_IdaeVolta}


And leaving ${Texto}
    Wait Until Element Is Visible  ${Voo.Input_Ida}  10
    Input Text                     ${Voo.Input_Ida}  ${Texto}
    Press Keys                     ${Voo.Input_Ida}  ARROW_DOWN
    Press Keys                     ${Voo.Input_Ida}  ENTER 