static char PROGMEM main_page[] = R"=====(
<!DOCTYPE html> 
<html> 
    <head> 
        <meta name='viewport' content='width=device-width, initial-scale=1.0'> 
        <style>
            #left{
                background-color: #FF0000;
                float: left;
                width: 49%;
                height: 70px;
            }
            #right{
                background-color: #0000FF;
                float: right;
                width: 49%;
                height: 70px;
            }
            #forward{
                background-color: #00FF00;
                width: 100%;
                height: 70px;
            }
        </style>
    </head>

    <style>
        #btn_adelante{
            position: absolute;
            top: 100px;
            left: 50%;
        }
        #btn_izq{
            position: absolute;
            top: 200px;
            left: 35%;
        }
        #btn_der{
            position: absolute;
            top: 200px;
            right: 35%;
        }
    </style>

    <script type='text/javascript'> 
        var modo_turbo = 'OFF';
        function cambiar_turbo(){
            if (modo_turbo == 'OFF'){
                document.getElementById('btn_turbo').value = "Apagar turbina :(";
                modo_turbo = 'ON';
            }else{
                document.getElementById('btn_turbo').value = "MODO TURBO!!!";
                modo_turbo = 'OFF';
            }

            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("info_turbo").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "turbo?modo=" + modo_turbo, true);
            xhttp.send();
        }

        function testMotors(){
            var xhttp = new XMLHttpRequest();
            /*xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("info_turbo").innerHTML = this.responseText;
                }
            };*/
            xhttp.open("POST", "testmotors", true);
            xhttp.send();
        }

        function goon(){
            var xhttp = new XMLHttpRequest();
            xhttp.open("POST", "goon", true);
            xhttp.send();
        }
        function goleft(){
            var xhttp = new XMLHttpRequest();
            xhttp.open("POST", "goleft", true);
            xhttp.send();
        }
        function goright(){
            var xhttp = new XMLHttpRequest();
            xhttp.open("POST", "goright", true);
            xhttp.send();
        }
        function stop(){
            var xhttp = new XMLHttpRequest();
            xhttp.open("POST", "stop", true);
            xhttp.send();
        }

    </script> 
    <body>
        Hola 123 hola hola ssssi si ssssi. <br/>

        <input id='btn_turbo' type='button' onclick='cambiar_turbo()' value='MODO TURBO!!!'/> 
        <label id='info_turbo'> </label><br/>

        <input type='button' onclick='testMotors()' value='mueva los huesos'/> <br/>
        <input id='btn_adelante' type='button'
            ontouchstart='goon()' ontouchend='stop()'
            onmousedown='goon()' onmouseup='stop()'
            value='^^'/> <br/>
        <input id='btn_izq' type='button' 
            ontouchstart='goleft()' ontouchend='stop()' 
            onmousedown='goleft()' onmouseup='stop()'
            value='<--'/> <br/>
        <input id='btn_der' type='button' 
            ontouchstart='goright()' ontouchend='stop()' 
            onmousedown='goright()' onmouseup='stop()'
            value='-->'/> <br/>
        <p id='forward' 
            ontouchstart='goon()' ontouchend='stop()'
            onmousedown='goon()' onmouseup='stop()'
        />
        <p id='left' 
            ontouchstart='goleft()' ontouchend='stop()' 
            onmousedown='goleft()' onmouseup='stop()'
        />
        <p id='right' 
            ontouchstart='goright()' ontouchend='stop()' 
            onmousedown='goright()' onmouseup='stop()'
        />
    </body>
</html>
)=====";