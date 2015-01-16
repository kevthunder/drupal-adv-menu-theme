# Advanced Menu Theming for Drupal 7

## Les templates possible

### `menu-tree(...)`
Contient ce qui est normalement un `<ul>`

### `menu-link(...)`
Contient ce qui est normalement un `<li>`

### `menu-link--lvl[0-9]` ou `menu-tree--lvl[0-9]`
Ces templates ne s'appliquerons uniquement pour le niveaux de profonder spécifier(lvl)

### `menu-link--[classname]`
Ces templates ne s'appliquerons que si l'item de menu contient la class spécifié (la class est configurable dans l'admin `/admin/structure/menu`)

### `menu-link--[classname]-child` ou `menu-tree--[classname]-child`
Ces templates sont appliqué à tous les sous menu qui sont enfant à un menu ayant la class spécifié

### `menu-link--lvl[0-9]--[classname]-child` ou `menu-link--lvl[0-9]--[classname]-child`
lvl et classname-child peuvent être combiner enssemble

## Example

### Pour généré ce menu :

```html
  <ul>
    <li>
      <span class="icon"></span><a href="/page1">Lorem Ipsum</a>
      <div>
        <ul>
          <li><a href="/page1">Lorem Ipsum</a></li>
        </ul>
      </div>
    </li>
    <li class="complex">
      <span class="icon"></span><a href="/page1">Lorem Ipsum</a>
      <div>
        <div class="left">
          <div class="item"><img src="thumbnail.jpg" alt="" /><a href="/page1">Lorem Ipsum</a></div>
        </div>
        <p>Lorem Ipsum. Donec sodales sagittis magna. Fusce convallis metus id felis luctus adipiscing.</p>
      </div>
    </li>
    <li>
      <span class="icon"></span><a href="/page1">Lorem Ipsum</a>
      <div>
        <ul>
          <li><a href="/page1">Lorem Ipsum</a></li>
          <li><a href="/page1">Lorem Ipsum</a></li>
        </ul>
      </div>
    </li>
    <li>
      <span class="icon"></span><a href="/page1">Lorem Ipsum</a>
    </li>
    <li>
      <span class="icon"></span><a href="/page1">Lorem Ipsum</a>
    </li>
    <li>
      <span class="icon"></span><a href="/page1">Lorem Ipsum</a>
    </li>
  </ul>
```

### Vous pouvez utiliser ces templates:

menu-link--main-menu--lvl0.tpl.php

```php
  <li<?php echo drupal_attributes($element['#attributes']); ?>>
    <span class="icon"></span><?php l($element['#title'], $element['#href'], $element['#localized_options']); ?>
    <?php echo drupal_render($element['#below']); ?>
  </li>
```

menu-tree--main-menu--lvl1.tpl.php

```php
  <div<?php echo drupal_attributes($variables['attributes']); ?>>
    <ul><?php echo $variables['tree']; ?></ul>
  </div>
```

menu-link--main-menu--complex.tpl.php

```php
  <li<?php echo drupal_attributes($element['#attributes']); ?>>
    <span class="icon"></span><?php l($element['#title'], $element['#href'], $element['#localized_options']); ?>
    <div>
      <?php echo drupal_render($element['#below']); ?>
      <p>Lorem Ipsum. Donec sodales sagittis magna. Fusce convallis metus id felis luctus adipiscing.</p>
    </div>
  </li>
```

menu-tree--main-menu--complex-child.tpl.php

```php
  <div<?php echo drupal_attributes($variables['attributes']); ?>><?php echo $variables['tree']; ?></div>
```

menu-link--main-menu--lvl1--complex-child.tpl.php

```php
  <div<?php echo drupal_attributes($element['#attributes']); ?>>
    <img src="thumbnail.jpg" alt=""><?php l($element['#title'], $element['#href'], $element['#localized_options']); ?>
    <?php echo drupal_render($element['#below']); ?>
  </div>
```