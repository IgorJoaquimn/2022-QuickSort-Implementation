# 2022-QuickSort-Implementation
The proposed problem was to perform an analysis of the number of occurrences of the words used in a text based on a new lexicographic order.

# Trabalho Prático 2

```
DCC214 - Estrutura de Dados
Igor Joaquim da Silva Costa
```
## 1. Introdução

Oproblemapropostofoirealizarumaanálisedonúmerodeocorrênciasdaspalavras
usadas em um texto baseada em uma nova ordem lexicográfica.
Para resolver o problema citado, foramusados dois algoritmos de ordenação,o
primeiro sendooQuicksortcommedianadeMelementoseosegundosendoaordenação
InsertionSort para textos pequenos, sempre considerando a nova ordem lexicográfica
requerida. Alémdisso,o programaécapazdecorrigireventuaisproblemasnoarquivode
entrada,realizandoaconversãodecaracteresacentuadosparaseurespectivopar,semacentos,
a união de palavras com hífen separadas por espaços em branco e a remoção de pontuação.
Diantedoexposto,adocumentaçãopresentepossuicomoobjetivodetalharcomoo
sistemafoiimplementado(Seção2),oquãoeficienteelepodeseremtermosteóricos(Seção
3) e aplicados (Seção 5), além de explicar como o programa lida com possíveis
inconsistênciasdurantesuaexecução(Seção4).Porfim,oprojetoésumarizadojuntocomos
aprendizados gerados durante a produção do trabalho(Seção 6).

## 2. Método

Estaseçãotemcomoobjetivodiscutirasdecisõesquelevaramàatualimplementação
do programa.

# 2.1 Fluxo principal

Antesdedetalharcomooprogramaoperasobreumtexto,valediscorrerdemaneira
textual e intuitiva o que oprogramafaza cadapassodeexecução.Primeiramente,cada
palavra presente no texto é lida e “ **normalizada** ”, ou seja,todo caracteremaiúsculo ou
acentuadoésubstituídoporseurespectivoparecadapontuaçãopresenteéretirada.Munidos
da nova ordemlexicográfica,oconjuntode palavrasé **ordenado** , deformaque palavras
repetidas ficam adjacentes e há a possibilidade de escolher quantos elementos serão


considerados na mediana. Após isso, é feita a **contagem** de quantasvezescada palavra
apareceu no texto, que fica salva em um arquivo.

# 2.2 Armazenamento

Afimdesuportarasoperaçõesdescritasacima,énecessárioumaestruturarobustao
suficienteparaguardarumsuperconjuntodepalavraseserpossíveldeencontrarqualquer
elemento de maneira rápida. Nesse sentido,a estrutura maisprática se mostrou ovetor
dinâmico,vistoqueomesmopossuitodasascaracterísticasnecessárias,alémdepodervariar

seutamanho durantea execução.Otamanhoinicialdovetoréde 105 elementos,número
grande escolhidoparanãoatrapalhar aexecuçãode testesdeperformance,visto quesão

necessáriasao menos 105 palavrasemumtextoparaqueoprogramagastenomínimo 60
segundos.Semprequeo tamanhodo textoformaiorque otamanhoatualdoarray,eleé

realocado com o dobro de elementosaté chegar no limite de 106 palavras, medida de
segurança para evitar overflow.

# 2.3 Normalização da Palavra

Como as palavras da saídaprecisam seguirumaformataçãoespecífica, setornou
válidaapresençadeumafunçãoque“normalize”aspalavraspresentes.Anormalizaçãose
tratadeumprocessoqueretiraqualquerpontuaçãoaomeiodapalavra,alémdetransformar
todasasletrasmaiúsculasemminúsculas.Paraeliminarapontuação,aformamaiscômoda
encontradafoiarmazenaroscaracteresproibidosemumastringeapartirdelafazerbuscasna
palavra,seoi-ésimoelementodapalavraestiverentreoscaracteresdepontuação,elenãoé
adicionado a nova string normalizada.

# 2.3 Normalização da Palavra [EXTRA]

Para tratareventuais problemasnoarquivodeentrada,afunçãodenormalizaçãoé
capazderetirarosacentosdalínguaportuguesapresentesnapalavra.Essaoperaçãopodeser
confusa ao usar o tipo string padrão de C++, isso porque caracteres especiais não são
representadosdamesmaformaqueoscaracteresnormais.Comoumastringéumalistade
palavras,nemtodosos 8 bitspresentesnotipocharsãousadosparacodificarseuconteúdo,
seusbitsiniciaissãousadosparacodificarqualopróximocharpresentenapalavra,fazendo


comque umtipocharpadrãodeC++sópossaarmazenarvaloresentre 0 e 127 databela
ASCII, o que é um problema, já que todo caractere especial possui um valor maior que 127.
Dessaforma,umcaractereespecialéformadodenomínimo 2 posiçõesdememória
dotipochar, dificultandosuaoperaçãodiretausandooperaçõesdestrings.Aformausada
pararesolveroproblemafoiusarumtipoalternativodestringfeitaespecialmenteparalidar
comesses“widechars”.ConvertendoastringdoC++emumvetordecharpadrão,épossível
contarquantasposiçõesdememóriacadacaracteredastringocupaeusaressainformação
parafazerumcastdestringparawstring,umtipoondecomparaçõescomcaracteresespeciais
são implementadas e funcionam da formacomque deveriam.Paraessefluxo funcionar,
usa-seabibliotecalocaleparaforçarqueoscaracteresadvindosdaentradaestejamnopadrão
UTF-8.

# 2.4 Ordenação QuickSort

Como especificadonaementado trabalho,a ordenaçãoé feitaa partirdométodo
QuickSort, queé umalgoritmode ordenaçãoque usadividireconquistarpararesolvero
problemadaordenação.ApremissadoQuickSorté,apartirdeumpivô, dividiroconjunto
em 2 subpartiçõesmenores,umacomelementosmenoresqueopivôeoutracomelementos
maioresqueopivô,fazendoissosucessivamenteparaassubpartiçõestemcomoresultadoum
vetor ordenado. Entretanto, existem formas de tornar esse algoritmo mais eficiente,
principalmenteaoescolhermoscomcautelaqualelementoseráopivôeaoordenarpartições
pequenas usando outros algoritmos maissimples que o QuickSort. Dessaforma, ambos
comportamentos foram implementados na função.

# 2.5 InsertionSort

Paraordenaraspartiçõesmenoreseencontraramedianadeumapartição,foiutilizado
o algoritmo deordenação InsetionSort.Aideiaportrás deleé queo maiorelementodo
conjuntosempreestaránaúltimaposição,dessaforma,bastairgradualmentecomparandoo
primeiroelementodovetorcomtodososoutros,atéchegarnofinal,seoelementocomparado
formenorouigualcomesseprimeiroelemento,elestrocamdelugar,aofinaldaexecução,
todo elemento está na sua devida posição.
Sendoassim,oInsertionSortéútilparalidarcompartiçõesjáordenadas,vistoqueos
elementosjáestãoemposiçãoenuncaocorreramtrocas.Dessaforma,elefoiescolhidopara
ordenaraspartiçõesmenores,jáqueelaspossuemumamaiorchancedejáestaremordenadas.


Damesmamaneira,elefoiescolhidoparaencontraramedianadapartição.Seapartiçãotiver
menoselementosqueonecessárioparacalcularamediana,éfeitaamedianade 2 elementos,
seapartiçãotivermenosque 2 elementoselanuncachamaráafunçãomediana,devidoao
caso base do QuickSort.

# 2.6 Comparação de palavras

Aprincipaloperaçãodaordenaçãoédecidirseumapalavraémenorqueoutra,no
casodanovaordemlexicográficapresentenoproblema,setornaválidaaexistênciadeuma
funçãobooleanaqueretornaseduaspalavrassãomenoresouiguais.Paraisso,foicriadoum
vetorde 26 inteirosquerepresentaanovaordemlexicográficadecadaumadas 26 letrasdo
alfabeto.Afimdecompararduaspalavras,bastaprocurarpelaposiçãodoprimeirocaractere
destoanteentreelaseretornarseaquelecaracterenaposiçãoencontradaémenorouigualao
caracterenastringdecomparação.Seessaposiçãonãoexistir,bastacompararotamanhodas
strings,seelastiveremomesmotamanho,elassãoamesmastring,senão,amenoréaquela
com o menor tamanho.

# 2.7 Contagem de palavras

Comaspalavrasjáordenadasnovetordepalavras,acontagemdepalavrasrepetidas
setornatrivial,vistoquetodapalavrarepetidaficaráadjacentedentrodovetor.Sendoassim,
bastaacriaçãodelistaauxiliaresparaarmazenaraspalavrasequantasvezeselasaparecem,
lendo linearmente a lista de palavras.

## 3. Análise de complexidade

# 3.1 Espaço

```
Inicialmente,écriadoumvetordepalavrasdetamanho 105 ,sendoassim,paratextos
```
commenosque 105 palavras,oespaçogastoéconstante.Entretanto,seotextotivermais
palavras que esse limite, mais memória é alocada e a complexidade se torna𝑂(𝑁) na
quantidade de palavras.


# 3.2 Tempo

```
Para análise de tempo, considere N o número de palavras do texto.
```
## 3.2 Ordenação

Paraserealizaraordenação,sãoutilizadosdoisalgoritmosemconjunto,oQuickSort
paralidarcompartiçõesmuitograndeseoInsertionSortparaordenarpartiçõesmenorese
encontrar medianas. Considerando a comparação como operação mais significativa, é
conhecidoqueoQuickSortefetua𝑂(𝑁*𝑙𝑜𝑔(𝑁))comparaçõesemvetoresdesordenadosem
média, jáqueacadachamadadométodotodososelementossãocomparadoumavezesão
realizadoscercade𝑙𝑜𝑔(𝑁)chamadas.Entretanto,esseargumentoéválidoapenasnoscasos
queaescolhadopivôfazcomqueoconjuntosejadivididoem 2 partesdetamanhopróximo,
seporacasoopivôforomenorouomaiorelementodoconjunto,todososdemaiselementos
ficamdentrodentrodamesmasub-partiçãoeaexecuçãodepassonãotrazmuitasmelhoras
na ordenação do conjunto. Essa propriedade é especialmente prejudicial em vetoresjá
ordenadosemordemcrescenteoudecrescente,transformandoonúmerodepassosde𝑙𝑜𝑔(𝑁)

para N, gerando uma complexidade de𝑂(𝑁^2 )nessescasos, que são os piores.
Outrossim, existem formas de evitar com que essescasos aconteçam.Aprimeira
maneiraé utilizaroalgoritmodeInsertionSortempartiçõespequenas.Talmétodoajudaa
mitigar o problema pois partições pequenas têm mais chancesdeestarem ordenadasem
relaçãoa partiçõesgrandes. Nessesentido,setornaválidaaanálisedoquãoeficazéessa
medida:

3.2.1 InsertionSort Para partições menores

Para entender como o InsertionSortpode ser benéfico se usado em conjunto ao
QuickSort,primeirosãonecessáriasalgumasanálisesepremissas.OInsertionSorté𝑂(𝑁) em
vetoresordenadosdeformacrescente,jáqueoelementousadoparaacomparaçãoésempre
menorqueoresto,nuncaacontecendocomparaçõesadicionaisparamudaroselementosde

lugar. Nos piores casos e nos casos médios,ele é 𝑂(𝑁^2 ),jáque cadaelementovaiser
comparadocomtodososoutrostodasasvezes,emmédia.Alémdisso,podemosconsiderar
que as entradas sempre será uma potência de 2, para facilitar a análise.


```
SendoSotamanhomínimonecessárioparaumapartiçãoserconsideradapequena,
```
podemosanalisarqualoefeitoqueoInsertionSortteráemumQuickSortcomentradaN= 2 𝑘
da seguinte maneira:

ComoNéumapotênciade2,aárvoredechamadasdométodoQuickSortcorresponde
aumaárvorebináriacompletadealturaKcom2N+ 1 nós,representandoototaldechamadas
recursivasfeitas,onde acada passootamanhodasub-partiçãocorrespondea 2 elevadoà
alturadonó.Entretanto,cadasubpartiçãocomtamanhomenorouigualaSdevesertratada
como InsertionSort.

Encontrarquaisnóspossuemessapropriedadeéfácil,seS= 2 𝑠,todososnóscom
alturamaiorque“s”vãosertratadospeloQuickSort,logo,oQuickSortvaiserexecutadonos
níveisentre 0 e(K-s),ouseja,entre 0 e𝑙𝑜𝑔(𝑁/𝑆).EmrelaçãoaoInsertionSort,eleserá

chamado apenasnonível“s”, quepossui 2 𝐾^ −^ 𝑠^ nós,detamanho 2 𝐿cada.Sendoassim,a
função de complexidade apenas do InsertionSort para partições pequenas é

```
𝑔(𝑁= 2 𝑘) = 2 𝐾^ −^ 𝑠*( 2 𝑠)^2 = 2 𝐾^ +𝑠 = 𝑁*𝑆
```
Da mesma maneira a função de complexidade do QuickSort fica:
ℎ(𝑁) =𝑁*(𝐾 − 𝑠)=𝑁*𝑙𝑜𝑔(𝑁/𝑆)

Sendo assim, a complexidade da ordenação no caso médio f(N) = g(N) + h(N) se torna:
𝑓(𝑁) = 𝑁*𝑙𝑜𝑔(𝑁/𝑆) + 𝑁*𝑆


Tomar S = N corresponde a executar o InsertionSort em todo conjunto, fazendo com que a
complexidade se torne quadrática. Se S for um valor pequeno em relação a N, a ordem de
complexidade se torna a mesma do QuickSort normal:

```
𝑓(𝑁) = 𝑁*𝑙𝑜𝑔(𝑁/𝑂( 1 ) ) + 𝑁*𝑂( 1 ) = 𝑂( 𝑁*𝑙𝑜𝑔(𝑁))
```
De maneira análoga, se a entrada for um conjunto ordenado de maneira crescente, cada
chamada do QuickSort diminui o tamanho da partição em 1, até que o tamanho do conjunto
seja S:

## X = N - S;

## 𝑓(𝑁) =

```
𝑖 = 1
```
```
𝑋
```
## ∑(𝑁 − 𝑖) + 𝑆

## 𝑓(𝑁) = 𝑋*(𝑁−𝑋 2 +^ 𝑁^ −^1 ) + 𝑆 = (𝑁−𝑆)*(𝑁 2 +^ 𝑆^ −^1 ) + 𝑆

## 𝑓(𝑁) = (𝑁 − 𝑆)² + 𝑆

Omesmoacontececomconjuntosordenadosdeformadecrescente,ouseja,seoNfor
pequenoosuficienteparaestarpróximodeS-ouoSgrandeosuficienteparaserpróximode
N-omelhorcaso setornalineareocasomédioficaquadrático,nãohavendograndeganho
assintóticoentreessemétodoeoInsertionSortpadrão.Entretanto,talsituaçãosóacontece,
porqueoalgoritmoaindaapresentaproblemasnahoradelidarcomconjuntosjáordenados,
sendo válida a estratégia da mediana de M elementos:

3.2.2 InsertionSort para mediana de M elementos

Entende-secomomedianadeumconjuntocomoovalorcentralpresentenele,sabendo
a medianadeconjuntodesordenado,é fácilsepará-lo em 2 subconjuntosdecomquasea
mesmaquantidadede elementos,tomandooselementosmenoresquea medianaparaum
conjuntoeosmaiores,paraoutro.NocontextodoQuickSort,opivôsemprecorresponderà
medianadesuapartiçãoconfiguraumaescolhaótima,jáqueapartiçãovaiserseparadaem


duasoutras subpartiçõesque tambémserãodivididassucessivamente,numtotaldelog(N)
vezes. Dessa forma, escolher a mediana como pivô garante que o QuickSort seja
𝑂( 𝑁𝑙𝑜𝑔(𝑁))em qualquer caso. Entretanto, encontrara mediana também possui um custo.
Como amedianaé ovalorcentraldapartição,aformamaisfácildeencontrá-laé
ordenarapartiçãoeescolheroelementonaposição𝑁/2,sóqueparaordenarapartiçãoéo
problema queestamostentando resolver.Umaoutraalternativaénãopegaramedianada
partiçãointeira,esim escolheramedianadosprimeirosMvalorespresentescomopivôe
trabalhar com ela, garantindo um aumento na eficiência geral do algoritmo.
Aindaassim,essaopçãotambémpossuiumcusto,quepodeserestimadodamesma
formafeita naseçãoanterior.Comodiscutidoanteriormente,ousodamedianafazcoma
funçãodecomplexidadedoalgoritmofique𝑁𝑙𝑜𝑔(𝑁)+Xemqualquercaso,ondeXéocusto
adicionalparacalcularasmedianas.Demaneirasimilar,amedianadeMelementossóserá

executadaenquantootamanhodapartiçãoanalisadaformaiorouigualaM,seN= 2 𝐾eM=

2 𝑚,issocorrespondeàtodososnóscomprofundidademenorque𝐾 − 𝑚 + 1 ,ouseja,

2 𝐾−𝑚+^1 − 1 ou( 2 𝑁𝑀 − 1 )nós.

Para cada um desses nós, é feita uma ordenação de M elementos usando o
InsertionSortparasedescobriramediana,essaoperaçãoéquadráticaemM,logo,sendod(N)
a função para calcular as medianas de uma entrada de tamanho N:


##### 𝑑(𝑁) =( 2 𝑁𝑀 − 1 )*𝑀^2 = 2 𝑁𝑀 − 𝑀^2

AfunçãodecomplexidadeparaM>2,quegarantequenuncaseráescolhidooumenorouo
maior elemento da partição fica:

```
𝑓(𝑁) =𝑁𝑙𝑜𝑔(𝑁) + 𝑑(𝑁) =𝑁𝑙𝑜𝑔(𝑁)+ 2 𝑁𝑀 − 𝑀^2
```
Se M for menor que 𝑙𝑜𝑔(𝑁), a função f(N) é O(Nlog(N)) emtodos os casos,
garantindoumaexecuçãopróximadeótimaparaoalgoritmoindependentedotipodeentrada,
isto porqueaspartiçõesquenãousarematécnicadamedianaserãopequenaseordenadas
peloInsertionSort,comoditonaseção3.2.1.Alémdisso,acombinaçãodamedianadeM
elementose aordenação simplesparapartições pequenasmelhoraaindamaisaconstante
envolvidanacomplexidadedoalgoritmo,vistoqueousodamedianaproporcionaumamaior
incidênciadesubpartiçõesjáordenadasdentreaschamadasrecursivasdoQuickSort,havendo
casos onde a função de complexidade se torna

```
𝑓(𝑁,𝑆,𝑀) =𝑁𝑙𝑜𝑔(𝑁𝑆) +𝑆 + 2 𝑁𝑀 − 𝑀^2 =𝑂(𝑁𝑙𝑜𝑔(𝑁))
```
se S e M forem suficientemente pequenos em comparação a N.
Porfim,conclui-seque,adependerdasescolhasdeSeMemrelaçãoaN,realizar
mais operações em conjunto ao QuickSort apresenta melhoras em sua complexidade
assintótica para alguns casos.

### 3.3 Busca

Considerandoacomparaçãocomoaoperaçãomaissignificativa,quetodabuscapelas
palavrasaconteceapós ovetorserordenadoe todapalavrarepetidaficaadjacenteapósa
ordenação,para-sebuscaraspalavrasrepetidas,sóénecessáriopercorrerovetorumavez,
checandoseoelementoatualéigualaopróximo.Dessaforma,contaraquantidadedevezes
que cada palavra acontece no texto é𝑂(𝑁).

### 3.4 Comparar Palavras.

Outroprocessoqueésignificativonaanálisedecomplexidadedoprogramaéoquão
bemelecompara seumapalavraémenorqueoutra.Aestratégiausadasegueumalógica
sequencial,varre-seamenorpalavra atéencontrar oprimeirocaracterequesejadiferente
entreasduas,seessecaracterenaprimeirapalavraformenorouigualàordemlexicográfica


do caractere na mesmaposiçãoda segundapalavra, retornaverdadeiro. Senãoexistirem
caracteresdiferentes,amenorpalavraéaquelaquepossuiomenortamanho.Dessaforma,a
comparação é𝑂(𝐿), onde L é o tamanho médio de umapalavra do texto.

## 3.5 Complexidade Geral.

Ditoisso,acomplexidadegeraldaordenaçãocorrespondeaoprodutoentreocustode
comparar as palavras e a quantidade de comparações feitas, ou seja:
𝑂(𝑁𝑙𝑜𝑔(𝑁)*𝐿)

## 4. Estratégias de Robustez

Aolidarcomlistasdestrings,aquantidadedememóriadisponívelparaoprograma
podefacilmenteserinsuficienteparasuaoperação,dessaforma,sãopermitidostextoscomno

máximo 106 palavras.

## 5. Análise Experimental

Aanáliseexperimentalaseguirtemcomoobjetivomediroquãoeficienteéosistema
implementadousandoduasmétricas,odesempenhocomputacional-quãorápidooprograma
é executado com entradas grandes - e análises de acesso em memória.

# 5.1 Desempenho computacional

## 5.1.1 Perfil de execução

Para testarodesempenhocomputacional,primeiramente,oprogramafoicompilado
em estadode "profiling",a fimde analisarquais funções consomemrelativamentemais
tempoduranteaexecuçãodoprograma.Diantedisso,foramfeitasbateriasdetestesapartir

detextosretiradosdeEbooksgratuitos,ondecadalivropossuicercade 105 palavras.Como
profile das execuções pronto, cada execução é processada pelo programa “gprof”,uma
ferramentaqueauxilianaanálisedodesempenhocomputacional.Ditoisso,segueaanálise
das chamadas de funções.


```
Tempo de
execução
(%)
```
```
Calls
```
```
46.24 49822106 isLessEqual(std::string,std::string)
16.18 81907 partition(std::string, int, int, int)
12.43 48317830 void std::swap<string,string>
10.40 _init
6.36 49822106 unsigned long const& std::min<unsigned long>
4.34 97118 normalize(string)
1.16 84939 insertionSort(std::string, int, int, int)
1.16 1 leitura_arquivo(std::basic_ifstream<char)
0.58 81907 mediana_simples(std::string, int, int, int)
0.58 1 start_order(int*)
```
Para evitar redundância, os outros perfis de execução apresentam o mesmo
comportamento dotesteapresentadoacima.Noquetangeaanálisedosexperimentos,fica
evidentequeafunçãoquemaisdemandatempo,emporcentagem,éafunçãoparacomparar
seumapalavraémenorqueoutra,jáqueessaéaoperaçãoprincipaldaordenação.Além
disso,afunçãoapresentacomplexidadelinearnotamanhodaspalavraseéchamadacercade
3 * 𝑁𝑙𝑜𝑔(𝑁) vezesduranteoprograma,usando afórmuladesenvolvida na seção3.2.2.
Dessaforma,afunçãode comparaçãoestaremprimeirolugarnão é degrandesurpresa,
embora existam formas de diminuir esse tempo de execução usando de técnicascomo
hashing.
Afunçãoqueocupaasegundaposiçãoéafunçãoqueparticionaovetorduranteo
QuickSort.
Oterceirolugarsetratadafunçãoquetrocadoiselementosdovetordeposição.Como
otextoutilizadonotestefoiretiradodeumlivro,existemmuitaspalavrasrepetidas,quefaz
comquemuitastrocasdeposiçõesocorram,vistoqueaoperaçãonecessáriaparaexecutar
umatrocaé aoperação menorouigual.Nessesentido,utilizarumcomparadorapenasde
igualdade teria diminuído o número de trocas e deixaria o programa mais eficiente.
Afunção_initqueocupaoquartolugarserveparacarregarecompartilharasfunções
dediferentesarquivosduranteaexecuçãodoprograma.Implementarafunçãodecomparação
no mesmo arquivo das funções de ordenação resolveria o problema.
Porfim,aúltimafunçãoválidaparasecomentaréanormalize,querepresentou4%do
tempodeexecuçãodoprograma.Estaéafunçãousadapararetirarletrasmaiúsculas,acentos


epontuaçõesdapalavraantesdelaserinserida.Paracadapalavranoarquivodeentrada,a
funçãonormalizeéchamada,fazendocomqueelatenhacomplexidadelinearnotamanhoda
entrada,sendojustoelasersignificativanotempodeexecuçãoparaaordenaçãodetextos
com muitos acentos.
Nessesentido,conclui-sequeaindaexistemmargensparaamelhoranodesempenho
doprograma,aníveldechamadasdefunções,vistoquemuitasdelaspoderiamserfeitasde
outras formas, a fim de melhor utilizar tempo de execução do programa.

### 5.1.2 Desempenho em termos da entrada

Alémdotempogasto pelaschamadasde funções, deve-semedirarelaçãoentreo
aumentodovolumedaentradadoprogramacomoseutempodeexecução.Pararealizartal
objetivo,foiutilizadaaferramentaMemlogdoprofessorWagnerMeiraeferramentasparaa
geração de gráficos. A seguir, o gráfico com os resultados.

Como visto acima,o tempodeexecuçãocresce muitopróximoaonlog(n), assim
como foi discutido na seção de análise de complexidade.
Para confirmar que o programa não performava de maneira quadrática, foram
realizados testes usando apenas o InsertionSort para ordenação:


```
Emboraosdoisgráficossejamparecidos,oInsertionSortrecebeuentradasdaordem
```
de 104 para ficar com um tempo de execução similarao QuickSort com entradas de 105.

Ográficoacimamostraoqueaconteceaovariaraescolhadamedianaedotamanho
da partiçãopequenacombasenotamanhodaentrada.Comumaanálisemaisdetalhada,é
possívelobservarqueaescolhadessesparâmetrosnãoafetamuitootempodeexecuçãopara
textoscommenosquemeiomilhãodepalavras,emboratextosgrandessebeneficiemdessa
técnica. Para elucidar tal fato, foram feitas baterias de testes com o texto de 500.000 palavras:


A partir do gráfico, é possível notar escolher mediana de M elementos com M
desnecessariamente grande pode piorar o tempo de execução do programa, tal fato é visto ao
avaliar que cada coluna colorida é maior do que a coluna anterior, para qualquer tamanho de
partição. Além disso, os menores tempos de execução ficaram nas escolhas de partição
próximas a Nlog(N), que nesse caso é 18.
Para além disso, foram feitos testes com valores de mediana e de partição extremos, o
primeiro sendo S = 50 e M = 500, que executou em 605 segundos, ou 10 minutos, e o caso
S = 500.000 M = 1, que executou em 1717 segundos, ou 28 minutos, que representa o valor
𝑁²para essa entrada. Por fim, vale ressaltar queo tempo de execução médio para o QuickSort
nessa entrada foi 25 segundos.

# 5.2 Análise de localidade de referência e acesso de memória

Comoexplicadoemaula,programaseficientesemusodememóriasãoaquelesque
tendemaacessarregiõesdememóriacontíguas,jáqueessapráticaéotimizadapelossistemas
operacionais onde o programa é executado. Tal propriedade échamadade localidadede
referência e é uma ótima métrica de como o programa acessa a memória por ele utilizada.
Nessesentido,munidodasferramentasAnalisamemeMemlog,disponibilizadaspelo
professorWagnerMeira,épossívelgerargráficosquedemonstramoacessodememóriado
programaemsuasdiversasfases,e,assim,analisarseoacessodememóriadoprograma
segue as boas práticas desejadas. Dito isso, segue a análise de acesso de memória e
localidadedereferência,ondeoid 0 representaainserçãodoselementosnovetor,oid 1 a
ordenação das partições pequenas pelo InsertionSort e o id 2 como os acessos do QuickSort.



Comovistoacima,oprogramaacessadiversasvezesposiçõesdememóriaadjacentes,
issoaconteceporqueoselementosestãodispostosportodoovetor.Dessaforma,éesperado
queadistânciadepilhasejaalta,vistoqueelementosdistantesnamemóriasãoacessadose
trocados de posição durante toda a execução do programa.


Dessaforma,conclui-sequeosistemanemsempremantémumabaixadistânciade
pilhadurante aexecução,desfavorecendo ahipótesedo acessoemposições contíguasde
memória e sendo uma flocalidade de referência.

### 6. Conclusões

Com ointuitode contarquantaspalavrasexistememumtexto,eapresentá-lasem
umanova ordemlexicográfica,foi implementadoumprograma queutilizaalgoritmosde
ordenação de forma não trivial para resolver o problema.


Duranteoprojetodosistemaforamlevadasemconsideraçãonãosóaspectospráticos
doprocessamentodetexto,mastambémcomoalinguagemdeprogramaçãoescolhidapoderia
serumaferramentaútil parachegarnoobjetivo esperado.Todaaquestãode mapearum
mini-mundo de interesse em um modelo computacional robusto se mostrou bastante
produtiva, levando o aluno a pensar em formas criativas de se resolver e entender o
problema,tendocomoresultadoumaextensadiscussãosobrecomoosmétodosdamedianae
daordenaçãosimplesparapartiçõespequenasafetamodesenvolvimentodoprograma.Por
fim,otempoextra usadoparaprojetarosistematrouxeváriasrecompensasnosentidoda
implementação, sendo um aspecto a ser levado para trabalhos futuros.
Além disso,os testese aanálise decomplexidade semostraram muitoúteispara
entendercomoasentradasinfluenciamaexecuçãodoprogramaecomoalgunsdetalhesde
implementação podem ser significativos em termos de desempenho computacional e
localidade de referência.
Nessesentido,todoofluxodetrabalhofoiessencialparaaconsolidaçãodeconteúdos
aprendidos emsala, além de apresentar,de formaprática,comosoftwaresmaiores, mais
consistentes e robustos são projetados e implementados.

### 7. Bibliografia:

Ziviani,N.(2006).ProjetosdeAlgoritmoscomImplementaçõesemJavaeC++:Capítulo3:
Estruturas de Dados Básicas. Editora Cengage.

Paulo Feofiloff, Notas de Aula da disciplina Projeto de Algoritmos (2018). DCC-IME-USP.
disponível em:https://www.ime.usp.br/~pf/algoritmos/aulas/


### 8. Instruções para compilação e execução:

### 8.1 Compilação

Existempartesdoprogramaquesãocompatíveisapenasàsversõesmaisrecentesda
linguagem c++, dito isso, deve-se seguir as seguintes configurações para a compilação:

```
Linguagem: C++
Compilador: Gnu g++
Flags de compilação:-std=c++11 -g
Versão da linguagem: standard C++1 1
Sistema operacional (preferência): distribuições baseadas no kernel Linux 5.15.
```
Ocomandoparacompilaroprogramaautomaticamenteestápresentenoarquivo **“Makefile”**
esuaexecuçãoéchamadapelocomando **“makeall”** .Aindaassim,seguemasinstruçõespara
compilar manualmente:

Parageraroexecutáveldoprograma,énecessário,primeiro,geraroobjetoparacadaarquivo
presentenapasta“/src”.Talobjetivopodeseralcançadoseguindoosseguintescomandosem
ordem:

```
g++ -g -std=c++11 -Wall -c src/main.cpp -o obj/main.o -I./include/
g++ -g -std=c++11 -Wall -c src/memlog.cpp -o obj/memlog.o -I./include/
g++ -g -std=c++11 -Wall -c src/ordenacao.cpp -o obj/ordenacao.o -I./include/
g++ -g -std=c++11 -Wall -c src/str_funcs.cpp -o obj/str_funcs.o -I./include/
```
Apósessepasso,deve-sejuntartodososobjetosemumúnicoarquivoexecutável,seguindoo
comando:
g++ -g-std=c++11-Wall -o./bin/tp2.out ./obj/main.o ./obj/memlog.o ./obj/ordenacao.o
./obj/str_funcs.o

Deste modo, o executável “/bin/tp2.out” estará compilado e pronto para ser utilizado.

#### 8.2 Execução

```
Seguem as instruções para a execução manual:
```

1. Certifique-se que o compilável foigeradode maneiracorreta,sealgum problema
    ocorrer, execute o comando “make all” presente no “Makefile”.
2. Dadoqueocompilávelfoigeradodemaneiracorreta,certifique-sequeoarquivode
    entrada existe. Se ele não existir, crie-o.
3. Certifique-sequeoarquivodeentradaestánaformataçãoesperada,ondeexisteum
    marcador#ORDEMparamarcaranovaordemlexicográficaeomarcador#TEXTO
    para marcar o texto a ser lido
4. Uma vez que os passos anteriores foram cumpridos, executeo programa com o
    comando: ./bin/tp2.out-i(entrada)-o(saida)-s(tamanhoparticao)-m(valorda
    mediana de m)
5. A saída estará guardada no arquivo de saida.



