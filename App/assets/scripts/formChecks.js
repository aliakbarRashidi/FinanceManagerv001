var namePattern = /^[A-Za-z0-9]+(?:[ _-][A-Za-z0-9]+)*$/;
var emailPattern = /(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])/;
var numberPattern = /^[0-9]*$/

function doLogin()
{
    if (passwordTextField.text.length === 0) {
        passwordTextField.hasError = true;
        passwordTextField.helperText = "Password cannot be empty!";
    } else if (emailTextField.text.length === 0) {
        emailTextField.hasError = true;
        emailTextField.helperText = "Email cannot be empty!";
    } else {
        SessionManager.Authenticate(emailTextField.text, "email", passwordTextField.text);
    }
}

function canRegister()
{
    return !(nameField.hasError || emailField.hasError || passwordField.hasError || passwordRetypeField.hasError)
}

function doRegister()
{
    if(canRegister())
        SessionManager.CreateAccount(nameField.text, emailField.text, passwordField.text, birthdayDatePicker.selectedDate)
    else
        console.log("Form is not correct")
}

function canCreateBudget()
{
    return !(nameField.hasError || descriptionField.hasError || valueField.hasError)
}

function createBudget()
{
    if(canCreateBudget())
        FinanceEngine.CreateBudget(nameField.text, descriptionField.text, expiryDatePicker.selectedDate, parseInt(valueField.text))
    else
        console.log("Form is not correct")
}

function getBudgetList(initial)
{
    if (!initial)
        budgetList = FinanceEngine.ListBudget(nameTextField.text, nameModifier.selectedText, nameLinker.selectedText,
                                            descriptionTextField.text, descriptionModifier.selectedText, descriptionLinker.selectedText,
                                            creationTextField.text, creationTimeModifier.selectedText, creationTimeLinker.selectedText,
                                            expiresFromTextField.text, expiresToTextField.text, expireTimeLinker.selectedText,
                                            expiredOptionGroup.current.text, expiredLinker.selectedText,
                                            valueTextField.text, valueModifier.selectedText)
    else
        budgetList = FinanceEngine.ListBudget("", "", "", "", "", "", "", "", "", "", "", "", "No", "AND", "", "")
}
