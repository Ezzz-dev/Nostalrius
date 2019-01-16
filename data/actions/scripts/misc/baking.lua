local ovens = {
	2535, 2537, 2539, 2541, 3510
}

local milestone = {
	1943, 1944, 1945, 1946
}

function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if item:getId() == 3603 then
		if (target:getId() == 2524 or target:getId() == 2873) and target:getFluidType() == FLUID_WATER then
			target:transform(target:getId(), FLUID_NONE)
			local parent = item:getParent()
			if parent:isContainer() or parent:isPlayer() then
				parent:addItem(3604, 1):decay()
			else
				Game.createItem(3604, 1, item:getPosition()):decay()
			end
			item:remove(1)
			return true
		end
	elseif item:getId() == 3604 then
		if table.contains(ovens, target:getId()) then
			Game.createItem(3600, 1, target:getPosition()) 
			item:remove(1)
			return true
		end
	elseif item:getId() == 3605 then
		if table.contains(milestone, target:getId()) then
			local parent = item:getParent()
			if parent:isContainer() or parent:isPlayer() then
				parent:addItem(3603, 1):decay()
			else
				Game.createItem(3603, 1, item:getPosition()):decay()
			end
			item:remove(1)
			return true
		end
	end
	return false
end
