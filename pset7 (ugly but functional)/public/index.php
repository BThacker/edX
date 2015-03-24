<?php

    // get information 
    require("../includes/config.php"); 
    $rows = query("SELECT id, symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);
    
    $cashq = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    $cashrow;
    $cash;
    if (count($cashq) == 1)
    {
        $cashrow = $cashq[0];
    }
    
            
    $positions = [];
    // apply information to array to be passed to portfolio
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "curcash" => $cashrow["cash"]
                ];
        }
    }

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio"]);

?>
