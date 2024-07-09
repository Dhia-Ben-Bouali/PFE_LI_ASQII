var a_envoyer = ""
var a_envoyer1 = ""
var for_pasma = "g"
var reset =""
var verif = ""
function Hamadi(){
     document.getElementById("ord").innerHTML = "8156-158";
     document.getElementById("med").innerHTML = "PANADOL/1";
     document.getElementById("medecin").innerHTML = "Dr. Paul";
     document.getElementById("date").innerHTML = "14/02/2023";
     document.getElementById("tir").innerHTML = "1";
     a_envoyer = "e"
     a_envoyer1 = "f"
     console.log(a_envoyer);
     console.log(a_envoyer1);

}

function Yousef(){
     document.getElementById("ord").innerHTML = "8547-325";
     document.getElementById("med").innerHTML = "DOLIPRANE/1";
     document.getElementById("medecin").innerHTML = "Dr. Ben Salah";
     document.getElementById("date").innerHTML = "23/01/2023";
     document.getElementById("tir").innerHTML = "2";
     a_envoyer = "c"
     a_envoyer1 = "b"
     console.log(a_envoyer);
     console.log(a_envoyer1);
}

function Marwa(){
     document.getElementById("ord").innerHTML = "8327-854";
     document.getElementById("med").innerHTML = "EFFERALGAN/2";
     document.getElementById("medecin").innerHTML = "Doc Maureen";
     document.getElementById("date").innerHTML = "04/01/2023";
     document.getElementById("tir").innerHTML = "3";
     a_envoyer = "a"
     a_envoyer1 = "d"
     console.log(a_envoyer);
     console.log(a_envoyer1);
}


function Samir(){
     document.getElementById("ord").innerHTML = "8987-542";
     document.getElementById("med").innerHTML = "PANADOL/2";
     document.getElementById("medecin").innerHTML = "Doc Richard";
     document.getElementById("date").innerHTML = "26/11/2023";
     document.getElementById("tir").innerHTML = "1";
     a_envoyer = "e"
     a_envoyer1 = "f"
}


function Sofiya(){
     document.getElementById("ord").innerHTML = "8547-563";
     document.getElementById("med").innerHTML = "EFFERALGAN/2";
     document.getElementById("medecin").innerHTML = "Doc Charlotte";
     document.getElementById("date").innerHTML = "13/04/2023";
     document.getElementById("tir").innerHTML = "3";
     a_envoyer = "a"
     a_envoyer1 = "d"
}


function Dhia(){
     document.getElementById("ord").innerHTML = "8547-528";
     document.getElementById("med").innerHTML = "MORPHIN/ 1";
     document.getElementById("medecin").innerHTML = "Doc Raymond";
     document.getElementById("date").innerHTML = "18/08/2023";
     document.getElementById("tir").innerHTML = "2";
     a_envoyer = "c"
     a_envoyer1 = "b"
}

function progress(){
     document.getElementById("titre").innerHTML = "Process";
     console.log("Haya");
     window.location = "ordonnce.html"; 
}

     // Replace with your app config object
     const firebaseConfig = {
          apiKey: "AIzaSyDsMba1SlZqk_uaGMJbutv1VT48SHks93U",
          authDomain: "djin-2022.firebaseapp.com",
          databaseURL: "https://djin-2022-default-rtdb.firebaseio.com",
          projectId: "djin-2022",
          storageBucket: "djin-2022.appspot.com",
          messagingSenderId: "560049578906",
          appId: "1:560049578906:web:ec9bfc29263093c3795023",
          measurementId: "G-P3Y7CJTL6S"
          };
      
// Initialize firebase
firebase.initializeApp(firebaseConfig);
      
// Make auth and database references
const auth = firebase.auth();
const db = firebase.database();
            
function writeData() {
     Openpopup();
     console.log(a_envoyer);
     console.log("done");
     firebase.database().ref("test").set({
     string: a_envoyer,
     });
     console.log("done");
     //progress();
     
}    
           
function writeData1() {
     console.log(a_envoyer1);
     console.log("done1");
     firebase.database().ref("test").set({
     string: a_envoyer1,
     });
     console.log("done");
     //progress();
} 
           
function tasjil_pasma() {
     console.log(for_pasma);
     console.log(" for_pasma done");
     firebase.database().ref("test1").set({
     string: for_pasma,
     });
     //progress();
}  

var popup = document.getElementById("popup");

function Openpopup(){
     console.log("houni");
     popup.classList.add("open-popup");
}
           
function Closepopup(){
     console.log("5rajt")
     popup.classList.remove("open-popup");
}

/*function verif_pasma() {
     console.log(for_pasma);
     console.log("for_pasma done");
     var ref = database.ref('test1');
     ref.once('value', function(snapshot) {
       console.log(snapshot.val());
     });
     if (verif=="ok"){
          Closepopup();
     }
     firebase.database().ref("test1").set({
          string: reset,
     });
}*/


/*it('should do something', function() {
     var valueFromFirstTest = global.mySharedData.someKey;
   });

   console.log(valueFromFirstTest); matimchich */
   
