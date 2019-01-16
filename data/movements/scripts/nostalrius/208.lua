function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32569, y = 32110, z = 07})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 32569, y = 32110, z = 07}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32569, y = 32110, z = 07})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 32569, y = 32110, z = 07}, 11)
end
