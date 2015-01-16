<?php
	
class AdvMenuThemeMenuItem {
	public $vars;
	public $parent_classes;
	public $depth;
	public $suggestions;
	
	function __construct(&$vars) {
		$this->vars = &$vars;
		
		$this->user_class = $this->_user_class();
		$this->vars['element']['#user_class'] = &$this->user_class;
		
		$this->parent_classes = $this->_parent_classes();
		$this->vars['element']['#parent_classes'] = &$this->parent_classes;
		
		$this->depth = count($this->parent_classes);
		$this->vars['element']['#depth'] = &$this->depth;
		
		$this->suggestions = $this->_suggestions();
		$this->vars['theme_hook_suggestions'] = &$this->suggestions;
	}
	
	function _parent_classes(){
		$next_classes = $parent_classes = !empty($this->vars['element']['#parent_classes']) ? $this->vars['element']['#parent_classes'] :  array();
		$next_classes[$this->vars['element']['#original_link']['mlid']] = $this->user_class;
		
		if ($this->vars['element']['#below']) {
			$this->vars['element']['#below']['#parent_classes'] = $next_classes;
			foreach( element_children($this->vars['element']['#below']) as $key){
				$this->vars['element']['#below'][$key]['#parent_classes'] = $next_classes;
			}
		}
		return $parent_classes;
	}
	
	function _user_class(){
		$exclude = array('active-trail','menu-'.$this->vars['element']['#original_link']['mlid']);
		$user_class = array();
		if(!empty($this->vars['element']['#localized_options']['attributes']['class'])){
			$user_class = array_diff($this->vars['element']['#localized_options']['attributes']['class'],$exclude);
			//kpr($user_class);
		}
		return $user_class;
	}
	function base_hook(){
		return $this->vars['theme_hook_original'];
	}
	function _class_for_suggestion($cls){
		return str_replace('-','_',$cls);
	}
	function _parent_based_suggestions(){
		$base = $this->base_hook();
		$suggestions = array();
		foreach($this->parent_classes as $classes){
			foreach($classes as $cls){
				$suggestions[] = $base.'__'.$this->_class_for_suggestion($cls).'_child';
				$suggestions[] = $base.'__lvl'.$this->depth.'__'.$this->_class_for_suggestion($cls).'_child';
			}
		}
		return $suggestions;
	}
	
	function _class_based_suggestions(){
		$base = $this->base_hook();
		$classes = $this->user_class;
		sort($classes);
		$classes = $this->_class_for_suggestion($classes);
		$toAdd = $classes;
		foreach(array_values($classes) as $start => $c){
			$len = count($toAdd);
			for ($i = $start; $i < $len; $i++) {
				$split = explode('__',$toAdd[$i]);
				if(!in_array($c,$split)){
					$split[] = $c;
					sort($split);
					$new = implode('__',$split);
					if(!in_array($new,$toAdd)){
						$toAdd[] = $new;
					}
				}
			}
		}
		foreach($toAdd as &$s){
			$s = $base.'__'.$s;
		}
		return $toAdd;
	}
	
	function _suggestions(){
		$base = $this->base_hook();
		$suggestions = array($base.'__lvl'.$this->depth);
		$suggestions = array_merge($suggestions,$this->_parent_based_suggestions(),$this->_class_based_suggestions());
		return $suggestions;
	}
	
}

?>