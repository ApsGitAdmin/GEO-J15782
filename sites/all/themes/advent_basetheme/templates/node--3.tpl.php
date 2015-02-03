<article<?php print $attributes; ?>>
  <?php print $user_picture; ?>
  <?php print render($title_prefix); ?>
  <h2><?php print $title; ?></h2>
  <?php if (!$page && $title): ?>
  <header>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
  </header>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  
  
  <div<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>
  <?php if ($display_submitted): ?>
  <footer class="submitted"><?php echo "Posted: " . date( "F j, Y",$node->created);?></footer>
  <?php endif; ?>  
  <div class="clearfix">
    <?php if (!empty($content['links'])): ?>
      <nav class="links node-links clearfix"><?php print render($content['links']); ?></nav>
    <?php endif; ?>

    
    <?php print render($content['comments']['comment_form']); ?>

    <script src="http://www.polleverywhere.com/polls/9oFk1FyiMNl8YzM/chart_widget.js?height=250&results_count_format=percent&width=300"></script>

  </div>
</article>