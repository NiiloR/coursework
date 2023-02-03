/**
 * TODO: 8.4 Register new user
 *       - Handle registration form submission
 *       - Prevent registration when password and passwordConfirmation do not match
 *       - Use createNotification() function from utils.js to show user messages of
 *       - error conditions and successful registration
 *       - Reset the form back to empty after successful registration
 *       - Use postOrPutJSON() function from utils.js to send your data back to server
 */


//const { emailInUse, saveNewUser } = require("../../utils/users");
document.getElementById("btnRegister").addEventListener("submit", () => {console.log("dsasadsa")});

const registerNewUser = async(event) => {
    console.log("TETETETE");
    const name = document.getElementById("name");
    const email = document.getElementById("email");
    const password = document.getElementById("password");
    const passwordConfirmation = document.getElementById("passwordConfirmation");
    if (passwordConfirmation != password) {
        createNotification("Password and Password Confirmation have to match", "notifications-container");
    }
    else {
        //const newUser = {...user};
        //newUser.name = name;
        //newUser.email = email;
        //newUser.password = password;
        const userData = { name: name, email: email, password: password }
        console.log(userData);
        //await postOrPutJSON("api/register", "POST", userData);
        
    }
};