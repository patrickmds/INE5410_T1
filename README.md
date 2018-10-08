# ine5408_T1

Trabalho 1 - Simulador de restaurante

O trabalho deve ser realizado em C usando pthreads. O simulador deve receber os seguintes argumentos de linha de comando:

 O número de cozinheiros;
 O número de fogões;
 O número de bocas de cada um desses fogões;
 O número de frigideiras;
 O número de garçons;
 Quantos pratos cabem no balcão de pratos prontos da cozinha.

Regras
Imageme meramente ilustrativa de uma cozinha

Cada cozinheiro só pode preparar um pedido por vez;
Um pedido tem que ser preparado por um único cozinheiro;
Um pedido tem apenas uma única receita (dentre as listadas abaixo);
Só pode haver uma ou zero panelas em uma boca de fogão em um dado momento;
Existem infinitas panelas, mas apenas um certo número de frigideiras
As tarefas que não mencionam frigideira são feitas em panelas
Algumas tarefas (partes da receita) não necessitam da atenção do cozinheiro: ele pode iniciá-las e depois se dedicar a outra tarefa da mesma receita, mesmo que essa segunda tarefa exija atenção. As tarefas que exigem atenção são denominadas de Dedicação Exclusiva [DE];
Um cozinheiro está livre se não está preparando um pedido;
Um cozinheiro está esperando se está preparando um pedido, mas aguardando uma sub-tarefa do pedido que não exige sua atenção;
Um cozinheiro está ocupado se está desempenhando uma tarefa que é parte de um pedido;
Um pedido só pode ser preparado por um cozinheiro livre;
Uma tarefa pode ser iniciada por um cozinheiro que esteja esperando;
Quando um cozinheiro termina um pedido, ele o coloca no balcão de pedidos prontos:
Se não houver espaço no balcão, o cozinheiro fica segurando o pedido na mão, até que seja liberado um espaço;
Qualquer garçom pode levar um pedido para qualquer cliente;
Todo garçom pega pedidos prontos no balcão e os entrega para os clientes;
Cada garçom pode entregar apenas um pedido de cada vez;
Você deve garantir que após o retorno da função main:
Não haja nenhuma outra thread em execução;
Não exista nenhum pedido em um estágio intermediário de produção ou já produzido mas não entregue;
Não podem haver memory leaks (use o AddressSanitizer para confirmar).
Funções principais:
notificar_prato_no_balcao(prato_t* prato): deve ser invocada para cada pedido imediatamente antes de um prato com o pedido ser colocado no balcão.
entregar_pedido(prato_t* prato): deve ser chamada quando um garçom entrega o prato correspondente a um pedido.
A cozinha deve operar com a melhor eficiência possível. Como as receitas possuem tarefas que não exigem a atenção do cozinheiro, é importante que ele inicie essas tarefas o mais cedo possível. Dica: para descobrir a estratégia ideal de início de tarefas, construa um diagrama para cada receita, representando as dependências entre as tarefas.

Receitas
Legenda:

[DE] -- Dedicação exclusiva
[Xmin] -- tarefa dura X minutos -- simulação do tempo já pronta em tarefas.{h,c}

Carne:
 Cortar a carne [5min] [DE]
 Temperar a carne [3min] [DE]
 Grelhar a carne em uma frigideira [3min] [DE]
 Empratar o pedido [1min] [DE]
Spaghetti:
Esquentar o molho [5min]
Ferver água [3min]
Cozinhar o Spaghetti (na água fervente) [5min]
Dourar o bacon em uma frigideira [2min]
Empratar o pedido [3min] [DE]
Sopa:
 Cortar legumes [10min] [DE]
 Ferver a água [3min]
 Fazer o caldo (com a água fervente, precisa de boca de fogão) [2min]
 Cozinhar os legumes no caldo [8min]
 Empratar o pedido [1min] [DE]



