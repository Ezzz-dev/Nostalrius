function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 2874 and target:getFluidType() == FLUID_OIL then 
		target:transform(target:getId(), FLUID_NONE)
		item:transform(2914, 1)
		item:decay()
		return true
	end
	return false
end
