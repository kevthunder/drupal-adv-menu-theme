<?php
	
class AdvMenuThemeMenuTree {
	public $vars;
	public $parent_classes;
	public $depth;
	public $suggestions;
	
	function __construct(&$vars) {
		$this->vars = &$vars;
		
		if(empty($this->vars['full_tree']['#parent_classes'])) $this->vars['full_tree']['#parent_classes'] = array();
		$this->parent_classes = &$this->vars['full_tree']['#parent_classes'];
		
		$this->depth = count($this->parent_classes);
		$this->vars['full_tree']['#depth'] = &$this->depth;
		
		$this->suggestions = $this->_suggestions();
		$this->vars['theme_hook_suggestions'] = &$this->suggestions;
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
	
	function _suggestions(){
		$base = $this->base_hook();
		$suggestions = array($base.'__lvl'.$this->depth);
		$suggestions = array_merge($suggestions,$this->_parent_based_suggestions());
		return $suggestions;
	}
	
}

?>