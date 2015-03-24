<div>
    </br>
    <a href="sell.php">SELL</a> <a href="buy.php">BUY</a> <a href="history.php">HISTORY</a> <a href="addfunds.php">Add Funds</a>
    </br>
<?php foreach ($positions as $position): ?>
    <tr>
        <td><?=$position["symbol"] ?></td>
        <td><?=$position["shares"] ?></td>
        <td><?=$position["price"] ?></td>
        <td><?=$position["curcash"] ?></td>
    </tr>
<?php endforeach ?>
<?php
    
  
?>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
