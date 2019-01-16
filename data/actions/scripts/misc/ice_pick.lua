function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if target:getId() == 4994 and player:getStorageValue(306) == 1 and player:getStorageValue(307) == 0 then 
		local parent = item:getParent()
		if parent:isContainer() or parent:isPlayer() then
			parent:addItem(4837, 1)
		else
			Game.createItem(4837, 1, item:getPosition())
		end
		target:getPosition():sendMagicEffect(2)
		player:setStorageValue(307, 1)
		return true
	end
	return false
end
