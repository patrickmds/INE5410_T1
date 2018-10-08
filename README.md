# ine5408_T1

Trabalho 1 - Simulador de restaurante

O trabalho deve ser realizado em C usando pthreads. O simulador deve receber os seguintes argumentos de linha de comando:

 O número de cozinheiros;<br/>
 O número de fogões;<br/>
 O número de bocas de cada um desses fogões;<br/>
 O número de frigideiras;<br/>
 O número de garçons;<br/>
 Quantos pratos cabem no balcão de pratos prontos da cozinha.<br/>

Regras

- Cada cozinheiro só pode preparar um pedido por vez;<br/>
- Um pedido tem que ser preparado por um único cozinheiro;<br/>
- Um pedido tem apenas uma única receita (dentre as listadas abaixo);<br/>
- Só pode haver uma ou zero panelas em uma boca de fogão em um dado momento;<br/>
- Existem infinitas panelas, mas apenas um certo número de frigideiras;<br/>
 &nbsp;&nbsp;&nbsp;&nbsp;As tarefas que não mencionam frigideira são feitas em panelas<br/>
- Algumas tarefas (partes da receita) não necessitam da atenção do cozinheiro: ele pode iniciá-las e depois se dedicar a outra tarefa da mesma receita, mesmo que essa segunda tarefa exija atenção. As tarefas que exigem atenção são denominadas de Dedicação Exclusiva [DE];<br/>
- Um cozinheiro está livre se não está preparando um pedido;<br/>
- Um cozinheiro está esperando se está preparando um pedido, mas aguardando uma sub-tarefa do pedido que não exige sua atenção;<br/>
- Um cozinheiro está ocupado se está desempenhando uma tarefa que é parte de um pedido;<br/>
- Um pedido só pode ser preparado por um cozinheiro livre;<br/>
- Uma tarefa pode ser iniciada por um cozinheiro que esteja esperando;<br/>
- Quando um cozinheiro termina um pedido, ele o coloca no balcão de pedidos prontos:<br/>
- Se não houver espaço no balcão, o cozinheiro fica segurando o pedido na mão, até que seja liberado um espaço;<br/>
- Qualquer garçom pode levar um pedido para qualquer cliente;<br/>
- Todo garçom pega pedidos prontos no balcão e os entrega para os clientes;<br/>
- Cada garçom pode entregar apenas um pedido de cada vez;<br/>


Você deve garantir que após o retorno da função main:<br/>
- Não haja nenhuma outra thread em execução;<br/>
- Não exista nenhum pedido em um estágio intermediário de produção ou já produzido mas não entregue;<br/>
- Não podem haver memory leaks (use o AddressSanitizer para confirmar).<br/>


Funções principais:<br/>
- notificar_prato_no_balcao(prato_t* prato): deve ser invocada para cada pedido imediatamente antes de um prato com o pedido ser colocado no balcão.<br/>
- entregar_pedido(prato_t* prato): deve ser chamada quando um garçom entrega o prato correspondente a um pedido.<br/>
- A cozinha deve operar com a melhor eficiência possível. Como as receitas possuem tarefas que não exigem a atenção do cozinheiro, é importante que ele inicie essas tarefas o mais cedo possível.<br/>


Receitas<br/>

[DE] -- Dedicação exclusiva<br/>
[Xmin] -- tarefa dura X minutos -- simulação do tempo já pronta em tarefas.{h,c}<br/>

- Carne:<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Cortar a carne [5min] [DE]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Temperar a carne [3min] [DE]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Grelhar a carne em uma frigideira [3min] [DE]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Empratar o pedido [1min] [DE]<br/>


- Spaghetti:<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Esquentar o molho [5min]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ferver água [3min]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Cozinhar o Spaghetti (na água fervente) [5min]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Dourar o bacon em uma frigideira [2min]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Empratar o pedido [3min] [DE]<br/>


- Sopa:<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Cortar legumes [10min] [DE]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Ferver a água [3min]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Fazer o caldo (com a água fervente, precisa de boca de fogão) [2min]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Cozinhar os legumes no caldo [8min]<br/>
&nbsp;&nbsp;&nbsp;&nbsp;Empratar o pedido [1min] [DE]<br/>



