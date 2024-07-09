function getLoginDetails() {
    const username = document.getElementById("username").value;
    let password = document.getElementById("password").value;
    console.log(username);
    console.log(password);
    if (username == "user" && password == "user") {
      console.log("hello");
      window.location = "info.html";
    } else {
      document.getElementById("username").value = "";
      document.getElementById("password").value = "";
      alert("Informations de connexion incorrectes. Veuillez réessayer.");
    
    }
}