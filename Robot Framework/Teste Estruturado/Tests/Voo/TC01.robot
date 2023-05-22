*** Settings ***
Resource    ../../Steps/Main_Steps.robot


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