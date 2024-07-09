setTimeout(() => {
  console.log("Delay!"); 
  document.getElementById("capteur").innerHTML= "Insérer votre empreinte";
}, 2000);

setTimeout(() => {
      console.log("Delay!"); 
      document.getElementById("capteur").innerHTML= "Retirer votre empreinte";
}, 4000);


setTimeout(() => {
      console.log("Delay!");
      document.getElementById("capteur").innerHTML= "Réinsérer votre empreinte"; 
}, 6000);
    

setTimeout(() => {
console.log("Delay!"); 
document.getElementById("capteur").innerHTML= "Empreinte enregistre";
}, 8000);


setTimeout(() => {
  console.log("Back!");
  window.location = "info.html";
}, 10000);

