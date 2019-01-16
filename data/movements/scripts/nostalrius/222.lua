function onStepIn(creature, item, position, fromPosition)
	doRelocate({x = 32481, y = 31905, z = 01},{x = 32480, y = 31905, z = 02})
	Game.sendMagicEffect({x = 32480, y = 31905, z = 02}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate({x = 32481, y = 31905, z = 01},{x = 32480, y = 31905, z = 02})
	Game.sendMagicEffect({x = 32480, y = 31905, z = 02}, 11)
end
