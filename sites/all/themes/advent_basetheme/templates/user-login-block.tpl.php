<div id="user-login-block-container">
  <div id="user-login-block-form-fields">
    <?php print $name; // Display username field ?>
    <?php print $pass; // Display Password field ?>
    <?php print $submit; // Display submit button ?>
    <div class="pass-btn">
	<a href="/user/password">Forgotton Password?</a>
 </div>
    <?php print $rendered; // Display hidden elements (required for successful login) ?> 
  </div>
 
 <div class="links">
 	<a class="reg-btn" href="/user/register">Register</a> 
  </div> 
</div>