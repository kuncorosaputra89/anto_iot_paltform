function turnOn(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function(){
        if (this.readyState == 4 & this.status == 200){
            console.log(this.responseText);
            var respond_split = this.responseText.split(",");
            var result = respond_split[0].split(":");
            if (result[1].slice(1,result[1].length-1)=="true"){
                document.getElementById("status").innerHTML = "Status: Turn On LED complete";
            }
        }
    };
    xhttp.open("GET","https://api.anto.io/channel/set/<<KEY>>/<<Thing>>/<<Channel>>/1",true);
    xhttp.send();
}

function  turnOff(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function(){
        if(this.readyState == 4 & this.status == 200){
            console.log(this.responseText);
            var respond_split = this.responseText.split(",");
            var result = respond_split[0].split(":");
            if(result[1].slice(1,result[1].length-1)=="true"){
                document.getElementById("status").innerHTML = "Status: Turn Off LED complete";
            }
        }
    };
    xhttp.open("GET","https://api.anto.io/channel/set/<<KEY>>/<<Thing>>/<<Channel>>/1",true);
    xhttp.send();
}