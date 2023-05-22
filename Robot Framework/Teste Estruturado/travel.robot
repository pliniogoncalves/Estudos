*** Settings ***
Library  SeleniumLibrary


*** Variables ***
#General Data
${URL}  https://www.phptravels.net/
${Browser}  chrome

#Test Data
${PrimeiroNome}  Edward
${UltimoNome}    Sheeran
${Telefone}      555-431
${Email}         teste@gmail.com
${Senha}         123456

#Home page elements
${A_Signup}    //a[@href="https://www.phptravels.net/signup"] 
${a_voos}     //a[contains(text(),"flights")] 
${A_Visto}   //a[@href="https://www.phptravels.net/visa"] 

#Registration page elements
${Input_PrimeiroNome}     //input[@placeholder="First Name"]
${Input_UltimoNome}      //input[@placeholder="Last Name"]
${Input_Telefone}       //input[@placeholder="Phone"]
${Input_Email}         //input[@placeholder="Email"]
${Input_Senha}        //input[@placeholder="Password"]
${Button_Account}     //button[id="ACCOUNT"]
${Button_Signup}     //button[@class="btn btn-default btn-lg btn-block effect ladda-button waves-effect"]
${Button_Cookie}    //button[@id="cookie_stop"]

#Login pages elements
${Input_EmailLogin}      //input[@placeholder="Email"] 
${Input_SenhaLogin}     //input[@placeholder="Password"]
${Button_Logar}        //span[contains(text(),"Login")]
${A_OpcaoLogin}      (//a[@href="https://www.phptravels.net/login"])[2]


#Flight page elements
${Input_IdaeVolta}              //input[@id="round-trip"]
${Input_Ida}                   //input[@id="autocomplete"]
${Input_Volta}                //input[@id="autocomplete2"] 
${Input_DataIda}            (//input[@id="departure"])[1]
${Input_DataVolta}         (//input[@id="return"])[1]
${A_PassageirosDrop}       //a[@href="#"]
${Div_QtdPassageiros}    (//div[@class="qtyInc"])[1]
${Button_PesquisarVoo}   //button[@id="flights-search"]

#Flight results page elements
${Button_PrimeiraOpcao}  (//button[@class="btn btn-primary btn-block theme-search-results-item-price-btn ladda waves-effect"])[1]

#Flight booking page
#Passenger 1
${Select_Nacionalidade}                      //select[@name="nationality_1"]
${Input_PrimeiroNomeReserva}                //input[@name="firstname_1"]
${Input_UltimoNomeReserva}                 //input[@name="lastname_1"]
${Select_MesNascimento}                   //select[@name="dob_month_1"]
${Input_DiaNascimento}                   //input[@name="dob_day_1"]
${Input_AnoNascimento}                  //input[@name="dob_year_1"]
${Input_PassportNumber}                //input[@name="passport_1"]
${Select_PassaportEmissaoMes}         //select[@name="passport_issuance_month_1"]
${Input_PassaporteEmissaoDia}        //input[@name="passport_issuance_day_1"]
${Input_PassaporteEmissaoAno}       //input[@name="passport_issuance_year_1"]
${Select_PassaporteExpiraMes}      //select[@name="passport_month_1"]
${Input_PassaporteExpiraDia}      //input[@name="passport_day_1"]
${Select_PassaporteExpiraMes}    //input[@name="passport_year_1"]

${Input_OpcaoPaypal}             (//input[@name="payment_gateway"])[4]
${Input_Termos}                  //input[@id="agreechb"]

#Booking page element
${H3_ReservaEfetuada}   //h3[contains(text(),"Booking Invoice")]

#Visa page elements
${Span_PaisOrigem}           (//span[@class="select2-selection select2-selection--single"])[1]
${Input_InformaPaisOrigem}   //input[@aria-controls="select2-from_country-results"]

*** Keywords ***

Given that I access php travels
    Open Browser  ${URL}  ${Browser}
    Maximize Browser Window

And register
    Wait Until Element Is Visible      ${A_Signup}            10
    Click Element                      ${A_Signup}
    Wait Until Element Is Visible      ${Input_PrimeiroNome}  10
    Input Text                         ${Input_PrimeiroNome}  ${PrimeiroNome}
    Wait Until Element Is Visible      ${Input_UltimoNome}    10
    Input Text                         ${Input_UltimoNome}    ${UltimoNome}     
    Wait Until Element Is Visible      ${Input_Telefone}      10
    Input Text                         ${Input_Telefone}      ${Telefone}  
    Wait Until Element Is Visible      ${Input_Email}         10
    Input Text                         ${Input_Email}         ${Email}  
    Wait Until Element Is Visible      ${Input_Senha}         10 
    Input Text                         ${Input_Senha}         ${Senha}
    Wait Until Element Is Visible      ${Button_Cookie}       10
    Click Element                      ${Button_Cookie}          
    Wait Until Element Is Visible      ${Button_Signup}       10 
    Sleep                              2s
    Run Keyword And Ignore Error       Click Element                      ${Button_Signup}    
    Click Element                      ${Button_Signup}

And log in
    Wait Until Element Is Visible  ${A_OpcaoLogin}      10
    Click Element                  ${A_OpcaoLogin} 
    Wait Until Element Is Visible  ${Input_EmailLogin}  10
    Input Text                     ${Input_EmailLogin}  ${Email}
    Wait Until Element Is Visible  ${Input_SenhaLogin}  10
    Input Text                     ${Input_SenhaLogin}  ${Senha}
    Run Keyword And Ignore Error   Wait Until Element Is Visible  ${Button_Cookie}     5
    Run Keyword And Ignore Error   Click Element                  ${Button_Cookie}
    Wait Until Element Is Visible  ${Button_Logar}      10
    Click Element                  ${Button_Logar} 

When I perform a round-trip flight search
    Wait Until Element Is Visible  ${a_voos}           10
    Click Element                  ${a_voos}
    Wait Until Element Is Visible  ${Input_IdaeVolta}  10
    Click Element                  ${Input_IdaeVolta}


And leaving ${Texto}
    Wait Until Element Is Visible  ${Input_Ida}  10
    Input Text                     ${Input_Ida}  ${Texto}
    Press Keys                     ${Input_Ida}  ARROW_DOWN
    Press Keys                     ${Input_Ida}  ENTER 

And going to ${Texto}


And leaving on date ${Texto}


And going back in date ${Texto}

And access to visa page
    Wait Until Element Is Visible  ${A_Visto}  10
    Click Element  ${A_Visto}

And i inform the country of origin being the ${Texto}
    Wait Until Element Is Visible  ${Span_PaisOrigem}  10
    Click Element                  ${Span_PaisOrigem}
    Wait Until Element Is Visible  ${Input_InformaPaisOrigem}  10
    Input Text                     ${Input_InformaPaisOrigem}  ${Texto}
    Press Keys                     ${Input_InformaPaisOrigem}  ENTER

And close the browser
    Close Browser



*** Test Cases ***
TC01 - Reservando passagem de destinos dentro dos EUA na classe econômica
    Given that I access php travels
    And register 
    And log in
    When I perform a round-trip flight search
    and leaving Los Angeles EUA
    #E indo para 
    #E saindo na data
    #E voltando na data
    #Quando eu clico em buscar
    #E seleciono o primeiro vôo
    #E preencho os dados do passageiro
    #E preencho os dados de pagamento
    #E clico em confirmar
    #Então a página de confirmação de viagem é exibida
    And close the browser

TC02 - Reservando passagens internacionais na classe econômica
    Given that I access php travels
    And register 
    And log in
    When I perform a round-trip flight search
    and leaving Salvador    
    #E indo para 
    #E saindo na data
    #E voltando na data
    #Quando eu clico em buscar
    #E seleciono o primeiro vôo
    #E preencho os dados do passageiro
    #E preencho os dados de pagamento
    #E clico em confirmar
    #Então a página de confirmação de viagem é exibida
    And close the browser
    

TC03 - Solicitar visto Americano
    Given that I access php travels
    And register 
    And log in
    And access to visa page
    And i inform the country of origin being the Brazil
    And close the browser