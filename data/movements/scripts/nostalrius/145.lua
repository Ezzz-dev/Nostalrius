function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33195, y = 32852, z = 04})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33195, y = 32852, z = 04}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33195, y = 32852, z = 04})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33195, y = 32852, z = 04}, 11)
end
