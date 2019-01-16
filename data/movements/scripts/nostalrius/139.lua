function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		creature:getPlayer():setStorageValue(274,1)
		item:getPosition():sendMagicEffect(13)
	end
end
