<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via a redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Search Quotes"]);
    }
    
    // else if the user reached this via POST (by submitting form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        render("quote.php");
    }
?>
