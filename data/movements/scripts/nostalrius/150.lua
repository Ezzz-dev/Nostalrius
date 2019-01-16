function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then
		doRelocate(item:getPosition(),{x = 33212, y = 31671, z = 13})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33212, y = 31671, z = 13}, 11)
		creature:getPlayer():setStorageValue(203,1)
	end
end
