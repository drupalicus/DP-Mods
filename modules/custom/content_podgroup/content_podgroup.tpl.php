<?php
// $Id$

/**
 * @file
 * THeme implmentation of content_podgroup.
 *
 * Theme implementation to display a podgroup.
 *
 * Available variables:
 * - $title: the (sanitized) title of the podgroup.
 * - $content: Content of the podgroup.
 * - $children: The rendered children of the podgroup
 * - $parent: An array of fields from the parent podgroup
 * - $class: The classes for css.
 *
 * Additional variables:
 * - $element: The raw element.
 *
 * @see template_preprocess()
 * @see template_preprocess_content_podgroup()
 */
?>

<fieldset class="<?php print $class; ?>">
  <?php if ($title): ?>
    <legend><?php print $title; ?></legend>
  <?php endif; ?>
  <div class="podgroup-content">
    <?php print $content ?>
  </div>
  <?php if ($children): ?>
    <div class="podgroup-children">
      <?php print $children; ?>
    </div>
  <?php endif; ?>
</fieldset>
